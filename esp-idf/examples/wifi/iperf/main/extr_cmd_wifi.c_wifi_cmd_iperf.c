#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {int flag; int dip; int sip; scalar_t__ interval; scalar_t__ time; void* dport; void* sport; } ;
typedef  TYPE_8__ iperf_cfg_t ;
typedef  int /*<<< orphan*/  cfg ;
struct TYPE_19__ {scalar_t__ count; scalar_t__* ival; } ;
struct TYPE_18__ {scalar_t__ count; scalar_t__* ival; } ;
struct TYPE_17__ {scalar_t__ count; void** ival; } ;
struct TYPE_16__ {scalar_t__ count; } ;
struct TYPE_15__ {scalar_t__ count; int /*<<< orphan*/ * sval; } ;
struct TYPE_14__ {scalar_t__ count; } ;
struct TYPE_13__ {scalar_t__ count; } ;
struct TYPE_12__ {TYPE_7__* time; TYPE_6__* interval; TYPE_5__* port; TYPE_4__* udp; TYPE_3__* ip; TYPE_2__* server; TYPE_1__* abort; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char*,char*,int,int,int,int,void*,int,int,int,int,void*,scalar_t__,scalar_t__) ; 
 void* IPERF_DEFAULT_INTERVAL ; 
 void* IPERF_DEFAULT_PORT ; 
 scalar_t__ IPERF_DEFAULT_TIME ; 
 int IPERF_FLAG_CLIENT ; 
 int IPERF_FLAG_SERVER ; 
 int IPERF_FLAG_TCP ; 
 int IPERF_FLAG_UDP ; 
 int /*<<< orphan*/  TAG ; 
 int arg_parse (int,char**,void**) ; 
 int /*<<< orphan*/  arg_print_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int esp_ip4addr_aton (int /*<<< orphan*/ ) ; 
 TYPE_11__ iperf_args ; 
 int /*<<< orphan*/  iperf_start (TYPE_8__*) ; 
 int /*<<< orphan*/  iperf_stop () ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int wifi_get_local_ip () ; 

__attribute__((used)) static int wifi_cmd_iperf(int argc, char** argv)
{
    int nerrors = arg_parse(argc, argv, (void**) &iperf_args);
    iperf_cfg_t cfg;

    if (nerrors != 0) {
        arg_print_errors(stderr, iperf_args.end, argv[0]);
        return 0;
    }

    memset(&cfg, 0, sizeof(cfg));

    if ( iperf_args.abort->count != 0) {
        iperf_stop();
        return 0;
    }

    if ( ((iperf_args.ip->count == 0) && (iperf_args.server->count == 0)) ||
         ((iperf_args.ip->count != 0) && (iperf_args.server->count != 0)) ) {
        ESP_LOGE(TAG, "should specific client/server mode");
        return 0;
    }

    if (iperf_args.ip->count == 0) {
        cfg.flag |= IPERF_FLAG_SERVER;
    } else {
        cfg.dip = esp_ip4addr_aton(iperf_args.ip->sval[0]);
        cfg.flag |= IPERF_FLAG_CLIENT;
    }

    cfg.sip = wifi_get_local_ip();
    if (cfg.sip == 0) {
        return 0;
    }

    if (iperf_args.udp->count == 0) {
        cfg.flag |= IPERF_FLAG_TCP;
    } else {
        cfg.flag |= IPERF_FLAG_UDP;
    }

    if (iperf_args.port->count == 0) {
        cfg.sport = IPERF_DEFAULT_PORT;
        cfg.dport = IPERF_DEFAULT_PORT;
    } else {
        if (cfg.flag & IPERF_FLAG_SERVER) {
            cfg.sport = iperf_args.port->ival[0];
            cfg.dport = IPERF_DEFAULT_PORT;
        } else {
            cfg.sport = IPERF_DEFAULT_PORT;
            cfg.dport = iperf_args.port->ival[0];
        }
    }

    if (iperf_args.interval->count == 0) {
        cfg.interval = IPERF_DEFAULT_INTERVAL;
    } else {
        cfg.interval = iperf_args.interval->ival[0];
        if (cfg.interval <= 0) {
            cfg.interval = IPERF_DEFAULT_INTERVAL;
        }
    }

    if (iperf_args.time->count == 0) {
        cfg.time = IPERF_DEFAULT_TIME;
    } else {
        cfg.time = iperf_args.time->ival[0];
        if (cfg.time <= cfg.interval) {
            cfg.time = cfg.interval;
        }
    }

    ESP_LOGI(TAG, "mode=%s-%s sip=%d.%d.%d.%d:%d, dip=%d.%d.%d.%d:%d, interval=%d, time=%d",
            cfg.flag&IPERF_FLAG_TCP?"tcp":"udp",
            cfg.flag&IPERF_FLAG_SERVER?"server":"client",
            cfg.sip&0xFF, (cfg.sip>>8)&0xFF, (cfg.sip>>16)&0xFF, (cfg.sip>>24)&0xFF, cfg.sport,
            cfg.dip&0xFF, (cfg.dip>>8)&0xFF, (cfg.dip>>16)&0xFF, (cfg.dip>>24)&0xFF, cfg.dport,
            cfg.interval, cfg.time);

    iperf_start(&cfg);

    return 0;
}