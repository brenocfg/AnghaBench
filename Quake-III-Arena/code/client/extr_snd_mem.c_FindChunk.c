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
 int /*<<< orphan*/  FindNextChunk (char*) ; 
 int /*<<< orphan*/  iff_data ; 
 int /*<<< orphan*/  last_chunk ; 

__attribute__((used)) static void FindChunk(char *name)
{
	last_chunk = iff_data;
	FindNextChunk (name);
}