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
struct nbio_stdio_t {scalar_t__ op; scalar_t__ progress; int /*<<< orphan*/  f; } ;

/* Variables and functions */
 scalar_t__ NBIO_READ ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbio_stdio_begin_read(void *data)
{
   struct nbio_stdio_t *handle = (struct nbio_stdio_t*)data;
   if (!handle)
      return;

   if (handle->op >= 0)
      abort();

   fseek(handle->f, 0, SEEK_SET);

   handle->op       = NBIO_READ;
   handle->progress = 0;
}