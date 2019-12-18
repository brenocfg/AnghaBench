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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  id_hdr_size; } ;
struct perf_session {int /*<<< orphan*/  machines; TYPE_1__ host_machine; int /*<<< orphan*/  evlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  machines__set_id_hdr_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__id_hdr_size (int /*<<< orphan*/ ) ; 

void perf_session__set_id_hdr_size(struct perf_session *session)
{
	u16 id_hdr_size = perf_evlist__id_hdr_size(session->evlist);

	session->host_machine.id_hdr_size = id_hdr_size;
	machines__set_id_hdr_size(&session->machines, id_hdr_size);
}