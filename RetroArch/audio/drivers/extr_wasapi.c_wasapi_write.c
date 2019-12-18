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
struct TYPE_4__ {scalar_t__ exclusive; scalar_t__ blocking; } ;
typedef  TYPE_1__ wasapi_t ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t wasapi_write_ex (TYPE_1__*,void const*,size_t) ; 
 size_t wasapi_write_sh (TYPE_1__*,void const*,size_t) ; 

__attribute__((used)) static ssize_t wasapi_write(void *wh, const void *data, size_t size)
{
   size_t written;
   wasapi_t *w = (wasapi_t*)wh;

   if (w->blocking)
   {
      ssize_t ir;
      for (written = 0, ir = -1; written < size; written += ir)
      {
         if (w->exclusive)
            ir = wasapi_write_ex(w, (char*)data + written, size - written);
         else
            ir = wasapi_write_sh(w, (char*)data + written, size - written);
         if (ir == -1)
            return -1;
      }
   }
   else if (w->exclusive)
      written = wasapi_write_ex(w, data, size);
   else
      written = wasapi_write_sh(w, data, size);

   return written;
}