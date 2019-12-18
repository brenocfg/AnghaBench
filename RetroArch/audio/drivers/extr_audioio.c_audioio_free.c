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
 int /*<<< orphan*/  AUDIO_FLUSH ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audioio_free(void *data)
{
   int *fd = (int*)data;

#ifdef AUDIO_FLUSH
   (void)ioctl(*fd, AUDIO_FLUSH, NULL);
#endif

   close(*fd);
   free(fd);
}