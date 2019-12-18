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

/* Variables and functions */
 int /*<<< orphan*/  MEMORY_GetCharset (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  charset ; 
 scalar_t__ initialised ; 

__attribute__((used)) static void BasicUIInit(void)
{
	if (!initialised) {
		MEMORY_GetCharset(charset);
		initialised = TRUE;
	}
}