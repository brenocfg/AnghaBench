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
typedef  int /*<<< orphan*/  u16 ;
struct m66592 {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  inw (unsigned long) ; 

__attribute__((used)) static inline u16 m66592_read(struct m66592 *m66592, unsigned long offset)
{
	return inw((unsigned long)m66592->reg + offset);
}