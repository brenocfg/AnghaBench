#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* pm_action ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * pm_buffer; } ;
struct TYPE_5__ {scalar_t__ pb_type; TYPE_2__ pb_memory; int /*<<< orphan*/ * pb_mbuf; } ;
typedef  TYPE_1__ pbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  PBUF_ACTION_DESTROY ; 
 scalar_t__ PBUF_TYPE_MBUF ; 
 scalar_t__ PBUF_TYPE_MEMORY ; 
 scalar_t__ PBUF_TYPE_ZOMBIE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
pbuf_destroy(pbuf_t *pbuf)
{

	if (pbuf->pb_type == PBUF_TYPE_MBUF) {
		if (pbuf->pb_mbuf) {
			m_freem(pbuf->pb_mbuf);
			pbuf->pb_mbuf = NULL;
		}
	} else
	if (pbuf->pb_type == PBUF_TYPE_MEMORY) {
		VERIFY(pbuf->pb_memory.pm_buffer != NULL);
		(void) (pbuf->pb_memory.pm_action)(&pbuf->pb_memory,
		    PBUF_ACTION_DESTROY);
	} else {
		VERIFY(pbuf->pb_type == PBUF_TYPE_ZOMBIE);
	}

	memset(pbuf, 0, sizeof(*pbuf));
}