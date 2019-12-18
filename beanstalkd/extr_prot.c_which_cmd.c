#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ Conn ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BURY ; 
 int /*<<< orphan*/  CMD_DELETE ; 
 int /*<<< orphan*/  CMD_IGNORE ; 
 int /*<<< orphan*/  CMD_KICK ; 
 int /*<<< orphan*/  CMD_KICKJOB ; 
 int /*<<< orphan*/  CMD_LIST_TUBES ; 
 int /*<<< orphan*/  CMD_LIST_TUBES_WATCHED ; 
 int /*<<< orphan*/  CMD_LIST_TUBE_USED ; 
 int /*<<< orphan*/  CMD_PAUSE_TUBE ; 
 int /*<<< orphan*/  CMD_PEEKJOB ; 
 int /*<<< orphan*/  CMD_PEEK_BURIED ; 
 int /*<<< orphan*/  CMD_PEEK_DELAYED ; 
 int /*<<< orphan*/  CMD_PEEK_READY ; 
 int /*<<< orphan*/  CMD_PUT ; 
 int /*<<< orphan*/  CMD_QUIT ; 
 int /*<<< orphan*/  CMD_RELEASE ; 
 int /*<<< orphan*/  CMD_RESERVE ; 
 int /*<<< orphan*/  CMD_RESERVE_JOB ; 
 int /*<<< orphan*/  CMD_RESERVE_TIMEOUT ; 
 int /*<<< orphan*/  CMD_STATS ; 
 int /*<<< orphan*/  CMD_STATSJOB ; 
 int /*<<< orphan*/  CMD_STATS_TUBE ; 
 int /*<<< orphan*/  CMD_TOUCH ; 
 int /*<<< orphan*/  CMD_USE ; 
 int /*<<< orphan*/  CMD_WATCH ; 
 int /*<<< orphan*/  OP_BURY ; 
 int /*<<< orphan*/  OP_DELETE ; 
 int /*<<< orphan*/  OP_IGNORE ; 
 int /*<<< orphan*/  OP_KICK ; 
 int /*<<< orphan*/  OP_KICKJOB ; 
 int /*<<< orphan*/  OP_LIST_TUBES ; 
 int /*<<< orphan*/  OP_LIST_TUBES_WATCHED ; 
 int /*<<< orphan*/  OP_LIST_TUBE_USED ; 
 int /*<<< orphan*/  OP_PAUSE_TUBE ; 
 int /*<<< orphan*/  OP_PEEKJOB ; 
 int /*<<< orphan*/  OP_PEEK_BURIED ; 
 int /*<<< orphan*/  OP_PEEK_DELAYED ; 
 int /*<<< orphan*/  OP_PEEK_READY ; 
 int /*<<< orphan*/  OP_PUT ; 
 int /*<<< orphan*/  OP_QUIT ; 
 int /*<<< orphan*/  OP_RELEASE ; 
 int /*<<< orphan*/  OP_RESERVE ; 
 int /*<<< orphan*/  OP_RESERVE_JOB ; 
 int /*<<< orphan*/  OP_RESERVE_TIMEOUT ; 
 int /*<<< orphan*/  OP_STATS ; 
 int /*<<< orphan*/  OP_STATSJOB ; 
 int /*<<< orphan*/  OP_STATS_TUBE ; 
 int /*<<< orphan*/  OP_TOUCH ; 
 int OP_UNKNOWN ; 
 int /*<<< orphan*/  OP_USE ; 
 int /*<<< orphan*/  OP_WATCH ; 
 int /*<<< orphan*/  TEST_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
which_cmd(Conn *c)
{
#define TEST_CMD(s,c,o) if (strncmp((s), (c), CONSTSTRLEN(c)) == 0) return (o);
    TEST_CMD(c->cmd, CMD_PUT, OP_PUT);
    TEST_CMD(c->cmd, CMD_PEEKJOB, OP_PEEKJOB);
    TEST_CMD(c->cmd, CMD_PEEK_READY, OP_PEEK_READY);
    TEST_CMD(c->cmd, CMD_PEEK_DELAYED, OP_PEEK_DELAYED);
    TEST_CMD(c->cmd, CMD_PEEK_BURIED, OP_PEEK_BURIED);
    TEST_CMD(c->cmd, CMD_RESERVE_TIMEOUT, OP_RESERVE_TIMEOUT);
    TEST_CMD(c->cmd, CMD_RESERVE_JOB, OP_RESERVE_JOB);
    TEST_CMD(c->cmd, CMD_RESERVE, OP_RESERVE);
    TEST_CMD(c->cmd, CMD_DELETE, OP_DELETE);
    TEST_CMD(c->cmd, CMD_RELEASE, OP_RELEASE);
    TEST_CMD(c->cmd, CMD_BURY, OP_BURY);
    TEST_CMD(c->cmd, CMD_KICK, OP_KICK);
    TEST_CMD(c->cmd, CMD_KICKJOB, OP_KICKJOB);
    TEST_CMD(c->cmd, CMD_TOUCH, OP_TOUCH);
    TEST_CMD(c->cmd, CMD_STATSJOB, OP_STATSJOB);
    TEST_CMD(c->cmd, CMD_STATS_TUBE, OP_STATS_TUBE);
    TEST_CMD(c->cmd, CMD_STATS, OP_STATS);
    TEST_CMD(c->cmd, CMD_USE, OP_USE);
    TEST_CMD(c->cmd, CMD_WATCH, OP_WATCH);
    TEST_CMD(c->cmd, CMD_IGNORE, OP_IGNORE);
    TEST_CMD(c->cmd, CMD_LIST_TUBES_WATCHED, OP_LIST_TUBES_WATCHED);
    TEST_CMD(c->cmd, CMD_LIST_TUBE_USED, OP_LIST_TUBE_USED);
    TEST_CMD(c->cmd, CMD_LIST_TUBES, OP_LIST_TUBES);
    TEST_CMD(c->cmd, CMD_QUIT, OP_QUIT);
    TEST_CMD(c->cmd, CMD_PAUSE_TUBE, OP_PAUSE_TUBE);
    return OP_UNKNOWN;
}