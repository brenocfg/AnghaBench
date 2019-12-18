#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct switch_log_entry {int spu_id; scalar_t__ val; scalar_t__ type; TYPE_2__ tstamp; scalar_t__ timebase; } ;
struct spu_context {TYPE_1__* switch_log; } ;
struct TYPE_3__ {int tail; struct switch_log_entry* log; } ;

/* Variables and functions */
 int SWITCH_LOG_BUFSIZE ; 
 int snprintf (char*,int,char*,unsigned int,unsigned int,int,unsigned int,unsigned int,unsigned long long) ; 

__attribute__((used)) static int switch_log_sprint(struct spu_context *ctx, char *tbuf, int n)
{
	struct switch_log_entry *p;

	p = ctx->switch_log->log + ctx->switch_log->tail % SWITCH_LOG_BUFSIZE;

	return snprintf(tbuf, n, "%u.%09u %d %u %u %llu\n",
			(unsigned int) p->tstamp.tv_sec,
			(unsigned int) p->tstamp.tv_nsec,
			p->spu_id,
			(unsigned int) p->type,
			(unsigned int) p->val,
			(unsigned long long) p->timebase);
}