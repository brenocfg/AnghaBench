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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nbio_t {int dummy; } ;
typedef  int /*<<< orphan*/  rpng_t ;

/* Variables and functions */
 int IMAGE_PROCESS_ERROR ; 
 int IMAGE_PROCESS_ERROR_END ; 
 int IMAGE_PROCESS_NEXT ; 
 int /*<<< orphan*/  NBIO_READ ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbio_begin_read (struct nbio_t*) ; 
 int /*<<< orphan*/  nbio_free (struct nbio_t*) ; 
 void* nbio_get_ptr (struct nbio_t*,size_t*) ; 
 int /*<<< orphan*/  nbio_iterate (struct nbio_t*) ; 
 scalar_t__ nbio_open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rpng_alloc () ; 
 int /*<<< orphan*/  rpng_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpng_is_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ rpng_iterate_image (int /*<<< orphan*/ *) ; 
 int rpng_process_image (int /*<<< orphan*/ *,void**,size_t,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  rpng_set_buf_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpng_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rpng_load_image_argb(const char *path, uint32_t **data,
      unsigned *width, unsigned *height)
{
   int retval;
   size_t file_len;
   bool              ret = true;
   rpng_t          *rpng = NULL;
   void             *ptr = NULL;
   struct nbio_t* handle = (struct nbio_t*)nbio_open(path, NBIO_READ);

   if (!handle)
      goto end;

   nbio_begin_read(handle);

   while (!nbio_iterate(handle));

   ptr = nbio_get_ptr(handle, &file_len);

   if (!ptr)
   {
      ret = false;
      goto end;
   }

   rpng = rpng_alloc();

   if (!rpng)
   {
      ret = false;
      goto end;
   }

   if (!rpng_set_buf_ptr(rpng, (uint8_t*)ptr))
   {
      ret = false;
      goto end;
   }

   if (!rpng_start(rpng))
   {
      ret = false;
      goto end;
   }

   while (rpng_iterate_image(rpng));

   if (!rpng_is_valid(rpng))
   {
      ret = false;
      goto end;
   }

   do
   {
      retval = rpng_process_image(rpng,
            (void**)data, file_len, width, height);
   }while(retval == IMAGE_PROCESS_NEXT);

   if (retval == IMAGE_PROCESS_ERROR || retval == IMAGE_PROCESS_ERROR_END)
      ret = false;

end:
   if (handle)
      nbio_free(handle);
   if (rpng)
      rpng_free(rpng);
   rpng = NULL;
   if (!ret)
      free(*data);
   return ret;
}