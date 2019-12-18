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
typedef  int /*<<< orphan*/  const uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  C255_P ; 
 int /*<<< orphan*/  br_i15_add (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i15_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
c255_sub(uint16_t *d, const uint16_t *a, const uint16_t *b)
{
	uint16_t t[18];

	memcpy(t, a, sizeof t);
	br_i15_add(t, C255_P, br_i15_sub(t, b, 1));
	memcpy(d, t, sizeof t);
}