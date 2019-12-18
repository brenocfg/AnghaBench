#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nbio_image_handle {int /*<<< orphan*/ * cb; int /*<<< orphan*/ * handle; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * handle; int /*<<< orphan*/ * data; int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ nbio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_transfer_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbio_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void task_image_cleanup(nbio_handle_t *nbio)
{
   struct nbio_image_handle *image = (struct nbio_image_handle*)nbio->data;

   if (image)
   {
      image_transfer_free(image->handle, image->type);

      image->handle                 = NULL;
      image->cb                     = NULL;
   }
   if (!string_is_empty(nbio->path))
      free(nbio->path);
   if (nbio->data)
      free(nbio->data);
   nbio_free(nbio->handle);
   nbio->path        = NULL;
   nbio->data        = NULL;
   nbio->handle      = NULL;
}