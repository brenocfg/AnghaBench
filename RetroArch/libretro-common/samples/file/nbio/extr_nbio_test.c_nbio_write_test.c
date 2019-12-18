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
struct nbio_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBIO_WRITE ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int /*<<< orphan*/  nbio_begin_write (struct nbio_t*) ; 
 int /*<<< orphan*/  nbio_free (struct nbio_t*) ; 
 void* nbio_get_ptr (struct nbio_t*,size_t*) ; 
 int /*<<< orphan*/  nbio_iterate (struct nbio_t*) ; 
 struct nbio_t* nbio_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbio_resize (struct nbio_t*,int) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void nbio_write_test(void)
{
   size_t size;
   bool looped = false;
   void* ptr = NULL;
   struct nbio_t* write = nbio_open("test.bin", NBIO_WRITE);
   if (!write)
      puts("[ERROR]: nbio_open failed (1)");

   nbio_resize(write, 1024*1024);

   ptr = nbio_get_ptr(write, &size);
   if (size != 1024*1024)
      puts("[ERROR]: wrong size (1)");

   memset(ptr, 0x42, 1024*1024);
   nbio_begin_write(write);

   while (!nbio_iterate(write))
      looped=true;

   if (!looped)
      puts("[SUCCESS]: Write finished immediately.");

   nbio_free(write);
}