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
struct Memory {scalar_t__ size; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 

__attribute__((used)) static void init_memory(struct Memory *chunk)
{
  chunk->memory = malloc(1);  /* grown as needed with realloc */
  chunk->size = 0;            /* no data at this point */
}