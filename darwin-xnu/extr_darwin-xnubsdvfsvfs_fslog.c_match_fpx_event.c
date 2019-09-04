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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  scalar_t__ uint32_t ;
struct fpx_event {scalar_t__ const fe_code; scalar_t__ const fe_xcpt; int /*<<< orphan*/  fe_uuid; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
match_fpx_event(const struct fpx_event *fe,
    const uuid_t uuid, const uint32_t code, const uint32_t xcpt)
{
	return (code == fe->fe_code && xcpt == fe->fe_xcpt &&
	    0 == memcmp(uuid, fe->fe_uuid, sizeof (uuid_t)));
}