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
struct cs4281 {scalar_t__ ba0; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void snd_cs4281_pokeBA0(struct cs4281 *chip, unsigned long offset,
				      unsigned int val)
{
        writel(val, chip->ba0 + offset);
}