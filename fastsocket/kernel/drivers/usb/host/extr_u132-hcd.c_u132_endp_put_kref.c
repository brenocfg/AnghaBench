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
struct u132_endp {int /*<<< orphan*/  kref; } ;
struct u132 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u132_endp_delete ; 

__attribute__((used)) static inline void u132_endp_put_kref(struct u132 *u132, struct u132_endp *endp)
{
	kref_put(&endp->kref, u132_endp_delete);
}