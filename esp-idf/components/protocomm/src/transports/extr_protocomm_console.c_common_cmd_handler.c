#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  sec_inst; TYPE_1__* sec; } ;
struct TYPE_4__ {int (* new_transport_session ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int ESP_ERR_INVALID_ARG ; 
 int ESP_OK ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int hex2bin (char*,int*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 TYPE_2__* pc_console ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int protocomm_req_handle (TYPE_2__*,char*,scalar_t__,int*,int,int**,int*) ; 
 scalar_t__ session_id ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int common_cmd_handler(int argc, char** argv)
{
    if (argc < 3) {
        return ESP_ERR_INVALID_ARG;
    }

    int i, ret;

    uint32_t cur_session_id = atoi(argv[1]);

    uint8_t *buf = (uint8_t *) malloc(strlen(argv[2]));
    uint8_t *outbuf;
    ssize_t outlen;
    ssize_t len = hex2bin(argv[2], buf);

    if (cur_session_id != session_id) {
        if (pc_console->sec && pc_console->sec->new_transport_session) {
            ret = pc_console->sec->new_transport_session(pc_console->sec_inst, cur_session_id);
            if (ret == ESP_OK) {
                session_id = cur_session_id;
            }
        }
    }

    ret = protocomm_req_handle(pc_console, argv[0], cur_session_id, buf, len, &outbuf, &outlen);
    free(buf);

    if (ret == ESP_OK) {
        printf("\r\n");
        for (i = 0; i < outlen; i++) {
            printf("%02x", outbuf[i]);
        }
        printf("\r\n");

        /* Transport is responsible for freeing the transmit buffer */
        free(outbuf);

        return ESP_OK;
    } else {
        return ret;
    }
}