#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_IMAGE_ENCODER ; 
 int /*<<< orphan*/  MMAL_ENCODING_BMP ; 
 int /*<<< orphan*/  MMAL_ENCODING_GIF ; 
 int /*<<< orphan*/  MMAL_ENCODING_JPEG ; 
 int /*<<< orphan*/  MMAL_ENCODING_PNG ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  bcm_host_init () ; 
 TYPE_1__* encoder ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmalCallback ; 
 int /*<<< orphan*/  mmal_encode_test (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mmal_wrapper_create (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_wrapper_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  sem ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

int main(int argc, const char** argv)
{
   bcm_host_init();

   if (vcos_semaphore_create(&sem, "encoder sem", 0) != VCOS_SUCCESS) {
      fprintf(stderr, "Failed to create semaphore\n");
      exit(1);
   }

   if (mmal_wrapper_create(&encoder, MMAL_COMPONENT_DEFAULT_IMAGE_ENCODER)
       != MMAL_SUCCESS) {
      fprintf(stderr, "Failed to create mmal component\n");
      exit(1);
   }
   encoder->callback = mmalCallback;

   // Perform test encodings in various formats
   mmal_encode_test(MMAL_ENCODING_PNG, "out.png");
   mmal_encode_test(MMAL_ENCODING_JPEG, "out.jpg");
   mmal_encode_test(MMAL_ENCODING_GIF, "out.gif");
   mmal_encode_test(MMAL_ENCODING_BMP, "out.bmp");

   mmal_wrapper_destroy(encoder);
   vcos_semaphore_delete(&sem);

   return 0;
}