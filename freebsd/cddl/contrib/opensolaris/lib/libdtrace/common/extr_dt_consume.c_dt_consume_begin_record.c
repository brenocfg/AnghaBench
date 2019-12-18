#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_probedata_t ;
struct TYPE_2__ {int (* dtbgn_recfunc ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dtbgn_arg; } ;
typedef  TYPE_1__ dt_begin_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_consume_begin_record(const dtrace_probedata_t *data,
    const dtrace_recdesc_t *rec, void *arg)
{
	dt_begin_t *begin = arg;

	return (begin->dtbgn_recfunc(data, rec, begin->dtbgn_arg));
}