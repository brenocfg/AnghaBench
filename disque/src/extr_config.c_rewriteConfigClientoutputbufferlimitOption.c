#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rewriteConfigState {int dummy; } ;
typedef  int /*<<< orphan*/  soft ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  hard ;
struct TYPE_6__ {scalar_t__ hard_limit_bytes; scalar_t__ soft_limit_bytes; scalar_t__ soft_limit_seconds; } ;
struct TYPE_5__ {TYPE_1__* client_obuf_limits; } ;
struct TYPE_4__ {scalar_t__ hard_limit_bytes; scalar_t__ soft_limit_bytes; scalar_t__ soft_limit_seconds; } ;

/* Variables and functions */
 int CLIENT_TYPE_COUNT ; 
 TYPE_3__* clientBufferLimitsDefaults ; 
 int /*<<< orphan*/  getClientTypeName (int) ; 
 int /*<<< orphan*/  rewriteConfigFormatMemory (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,long) ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_2__ server ; 

void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state) {
    int j;
    char *option = "client-output-buffer-limit";

    for (j = 0; j < CLIENT_TYPE_COUNT; j++) {
        int force = (server.client_obuf_limits[j].hard_limit_bytes !=
                    clientBufferLimitsDefaults[j].hard_limit_bytes) ||
                    (server.client_obuf_limits[j].soft_limit_bytes !=
                    clientBufferLimitsDefaults[j].soft_limit_bytes) ||
                    (server.client_obuf_limits[j].soft_limit_seconds !=
                    clientBufferLimitsDefaults[j].soft_limit_seconds);
        sds line;
        char hard[64], soft[64];

        rewriteConfigFormatMemory(hard,sizeof(hard),
                server.client_obuf_limits[j].hard_limit_bytes);
        rewriteConfigFormatMemory(soft,sizeof(soft),
                server.client_obuf_limits[j].soft_limit_bytes);

        line = sdscatprintf(sdsempty(),"%s %s %s %s %ld",
                option, getClientTypeName(j), hard, soft,
                (long) server.client_obuf_limits[j].soft_limit_seconds);
        rewriteConfigRewriteLine(state,option,line,force);
    }
}