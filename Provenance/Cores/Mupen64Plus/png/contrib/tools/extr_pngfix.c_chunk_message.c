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
struct chunk {int /*<<< orphan*/  chunk_type; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  type_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
chunk_message(struct chunk *chunk, const char *message)
{
   type_message(chunk->file, chunk->chunk_type, message);
}