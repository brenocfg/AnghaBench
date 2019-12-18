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
struct nbio_stdio_t {size_t len; size_t progress; int op; int /*<<< orphan*/  f; scalar_t__ data; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  BIO_WRITE ; 
#define  NBIO_READ 129 
#define  NBIO_WRITE 128 
 int /*<<< orphan*/  fread (char*,int,size_t,int /*<<< orphan*/ ) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nbio_stdio_iterate(void *data)
{
   size_t amount               = 65536;
   struct nbio_stdio_t *handle = (struct nbio_stdio_t*)data;

   if (!handle)
      return false;

   if (amount > handle->len - handle->progress)
      amount = handle->len - handle->progress;

   switch (handle->op)
   {
      case NBIO_READ:
         if (handle->mode == BIO_READ)
         {
            amount = handle->len;
            fread((char*)handle->data, 1, amount, handle->f);
         }
         else
            fread((char*)handle->data + handle->progress, 1, amount, handle->f);
         break;
      case NBIO_WRITE:
         if (handle->mode == BIO_WRITE)
         {
            size_t written = 0;
            amount = handle->len;
            written = fwrite((char*)handle->data, 1, amount, handle->f);
            if (written != amount)
               return false;
         }
         else
            fwrite((char*)handle->data + handle->progress, 1, amount, handle->f);
         break;
   }

   handle->progress += amount;

   if (handle->progress == handle->len)
      handle->op = -1;
   return (handle->op < 0);
}