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
struct oti6858_buf {struct oti6858_buf* buf_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct oti6858_buf*) ; 

__attribute__((used)) static void oti6858_buf_free(struct oti6858_buf *pb)
{
	if (pb) {
		kfree(pb->buf_buf);
		kfree(pb);
	}
}