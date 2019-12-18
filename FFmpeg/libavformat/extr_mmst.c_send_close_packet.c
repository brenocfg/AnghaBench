#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mms; } ;
typedef  TYPE_1__ MMSTContext ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PKT_STREAM_CLOSE ; 
 int /*<<< orphan*/  insert_command_prefixes (int /*<<< orphan*/ *,int,int) ; 
 int send_command_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  start_command_packet (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_close_packet(MMSTContext *mmst)
{
    start_command_packet(mmst, CS_PKT_STREAM_CLOSE);
    insert_command_prefixes(&mmst->mms, 1, 1);

    return send_command_packet(mmst);
}