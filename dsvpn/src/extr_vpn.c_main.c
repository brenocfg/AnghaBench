#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int is_server; char* server_ip_or_name; char* server_port; char* wanted_if_name; char* local_tun_ip; char* remote_tun_ip; char* wanted_ext_gw_ip; int tun_fd; char* if_name; int firewall_rules_set; int /*<<< orphan*/  server_ip; int /*<<< orphan*/ * ext_if_name; int /*<<< orphan*/  ext_gw_ip; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 char* DEFAULT_CLIENT_IP ; 
 int /*<<< orphan*/  DEFAULT_MTU ; 
 char* DEFAULT_PORT ; 
 char* DEFAULT_SERVER_IP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ doit (TYPE_1__*) ; 
 scalar_t__ firewall_rules (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * get_default_ext_if_name () ; 
 char* get_default_gw_ip () ; 
 int /*<<< orphan*/  get_tun6_addresses (TYPE_1__*) ; 
 scalar_t__ load_key_file (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pledge (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ resolve_ip (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int tun_create (char*,char*) ; 
 scalar_t__ tun_set_mtu (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
    Context     context;
    const char *ext_gw_ip;

    if (argc < 3) {
        usage();
    }
    memset(&context, 0, sizeof context);
    context.is_server = strcmp(argv[1], "server") == 0;
    if (load_key_file(&context, argv[2]) != 0) {
        fprintf(stderr, "Unable to load the key file [%s]\n", argv[2]);
        return 1;
    }
    context.server_ip_or_name = (argc <= 3 || strcmp(argv[3], "auto") == 0) ? NULL : argv[3];
    if (context.server_ip_or_name == NULL && !context.is_server) {
        usage();
    }
    context.server_port    = (argc <= 4 || strcmp(argv[4], "auto") == 0) ? DEFAULT_PORT : argv[4];
    context.wanted_if_name = (argc <= 5 || strcmp(argv[5], "auto") == 0) ? NULL : argv[5];
    context.local_tun_ip   = (argc <= 6 || strcmp(argv[6], "auto") == 0)
                               ? (context.is_server ? DEFAULT_SERVER_IP : DEFAULT_CLIENT_IP)
                               : argv[6];
    context.remote_tun_ip = (argc <= 7 || strcmp(argv[7], "auto") == 0)
                                ? (context.is_server ? DEFAULT_CLIENT_IP : DEFAULT_SERVER_IP)
                                : argv[7];
    context.wanted_ext_gw_ip = (argc <= 8 || strcmp(argv[8], "auto") == 0) ? NULL : argv[8];
    ext_gw_ip = context.wanted_ext_gw_ip ? context.wanted_ext_gw_ip : get_default_gw_ip();
    snprintf(context.ext_gw_ip, sizeof context.ext_gw_ip, "%s", ext_gw_ip == NULL ? "" : ext_gw_ip);
    if (ext_gw_ip == NULL && !context.is_server) {
        fprintf(stderr, "Unable to automatically determine the gateway IP\n");
        return 1;
    }
    if ((context.ext_if_name = get_default_ext_if_name()) == NULL && context.is_server) {
        fprintf(stderr, "Unable to automatically determine the external interface\n");
        return 1;
    }
    get_tun6_addresses(&context);
    context.tun_fd = tun_create(context.if_name, context.wanted_if_name);
    if (context.tun_fd == -1) {
        perror("tun device creation");
        return 1;
    }
    printf("Interface: [%s]\n", context.if_name);
    if (tun_set_mtu(context.if_name, DEFAULT_MTU) != 0) {
        perror("mtu");
    }
#ifdef __OpenBSD__
    pledge("stdio proc exec dns inet", NULL);
#endif
    context.firewall_rules_set = -1;
    if (context.server_ip_or_name != NULL &&
        resolve_ip(context.server_ip, sizeof context.server_ip, context.server_ip_or_name) != 0) {
        firewall_rules(&context, 0, 1);
        return 1;
    }
    if (context.is_server) {
        if (firewall_rules(&context, 1, 0) != 0) {
            return -1;
        }
#ifdef __OpenBSD__
        printf("\nAdd the following rule to /etc/pf.conf:\npass out from %s nat-to egress\n\n",
               context.remote_tun_ip);
#endif
    } else {
        firewall_rules(&context, 0, 1);
    }
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    if (doit(&context) != 0) {
        return -1;
    }
    firewall_rules(&context, 0, 0);
    puts("Done.");

    return 0;
}