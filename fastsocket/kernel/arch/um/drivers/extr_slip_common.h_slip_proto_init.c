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
struct slip_proto {scalar_t__ esc; scalar_t__ pos; scalar_t__ more; int /*<<< orphan*/  obuf; int /*<<< orphan*/  ibuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void slip_proto_init(struct slip_proto * slip)
{
	memset(slip->ibuf, 0, sizeof(slip->ibuf));
	memset(slip->obuf, 0, sizeof(slip->obuf));
	slip->more = 0;
	slip->pos = 0;
	slip->esc = 0;
}