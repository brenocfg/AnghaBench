#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* (* init ) (char const*) ;} ;
typedef  TYPE_1__ input_driver_t ;
struct TYPE_9__ {void* (* init ) (char const*) ;} ;
struct TYPE_8__ {void* (* init ) (char const*) ;} ;

/* Variables and functions */
 TYPE_1__ input_dinput ; 
 TYPE_4__ input_uwp ; 
 TYPE_1__ input_winraw ; 
 TYPE_2__ input_xinput ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 void* stub1 (char const*) ; 
 void* stub2 (char const*) ; 
 void* stub3 (char const*) ; 
 void* stub4 (char const*) ; 
 void* stub5 (char const*) ; 

void d3d_input_driver(const char* input_name, const char* joypad_name,
      input_driver_t** input, void** input_data)
{
#if defined(__WINRT__)
   /* Plain xinput is supported on UWP, but it
    * supports joypad only (uwp driver was added later) */
   if (string_is_equal(input_name, "xinput"))
   {
      void *xinput = input_xinput.init(joypad_name);
      *input = xinput ? (input_driver_t*)&input_xinput : NULL;
      *input_data = xinput;
   }
   else
   {
      void *uwp = input_uwp.init(joypad_name);
      *input = uwp ? (input_driver_t*)&input_uwp : NULL;
      *input_data = uwp;
   }
#elif defined(_XBOX)
   void *xinput = input_xinput.init(joypad_name);
   *input = xinput ? (input_driver_t*)&input_xinput : NULL;
   *input_data = xinput;
#else
#if _WIN32_WINNT >= 0x0501
   /* winraw only available since XP */
   if (string_is_equal(input_name, "raw"))
   {
      *input_data = input_winraw.init(joypad_name);
      if (*input_data)
      {
         *input = &input_winraw;
         return;
      }
   }
#endif

#ifdef HAVE_DINPUT
   *input_data = input_dinput.init(joypad_name);
   *input = *input_data ? &input_dinput : NULL;
#endif
#endif
}