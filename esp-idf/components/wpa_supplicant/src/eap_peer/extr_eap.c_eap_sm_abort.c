#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct eap_sm {int /*<<< orphan*/ * lastRespData; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void eap_sm_abort(struct eap_sm *sm)
{
	wpabuf_free(sm->lastRespData);
	sm->lastRespData = NULL;
}