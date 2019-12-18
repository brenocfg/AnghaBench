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
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
typedef  unsigned int uint32_t ;
typedef  void string_list ;
struct TYPE_3__ {int /*<<< orphan*/  DisplayName; } ;
typedef  TYPE_1__ XAUDIO2_DEVICE_DETAILS ;
typedef  int /*<<< orphan*/  IXAudio2 ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXAudio2_GetDeviceCount (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ IXAudio2_GetDeviceDetails (int /*<<< orphan*/ *,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  IXAudio2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  XAUDIO2_DEFAULT_PROCESSOR ; 
 int /*<<< orphan*/  XAudio2Create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* mmdevice_list_new (void*) ; 
 int /*<<< orphan*/  string_list_append (void*,char*,union string_list_elem_attr) ; 
 void* string_list_new () ; 
 char* utf16_to_utf8_string_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *xa_list_new(void *u)
{
#if defined(_XBOX) || !(_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
   unsigned i;
   union string_list_elem_attr attr;
   uint32_t dev_count              = 0;
   IXAudio2 *ixa2                  = NULL;
   struct string_list *sl          = string_list_new();

   if (!sl)
      return NULL;

   attr.i = 0;

   if (FAILED(XAudio2Create(&ixa2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
      return NULL;

   IXAudio2_GetDeviceCount(ixa2, &dev_count);

   for (i = 0; i < dev_count; i++)
   {
      XAUDIO2_DEVICE_DETAILS dev_detail;
      if (IXAudio2_GetDeviceDetails(ixa2, i, &dev_detail) == S_OK)
      {
         char *str = utf16_to_utf8_string_alloc(dev_detail.DisplayName);

         if (str)
         {
            string_list_append(sl, str, attr);
            free(str);
         }
      }
   }

   IXAudio2_Release(ixa2);

   return sl;
#elif defined(__WINRT__)
   return NULL;
#else
   return mmdevice_list_new(u);
#endif
}