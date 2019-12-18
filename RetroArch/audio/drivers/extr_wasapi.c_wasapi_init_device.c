#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {unsigned int size; TYPE_1__* elems; } ;
typedef  int int32_t ;
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  IMMDeviceEnumerator ;
typedef  int /*<<< orphan*/  IMMDeviceCollection ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/ **** CLSID_MMDeviceEnumerator ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *****,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *****,void**) ; 
 int /*<<< orphan*/  DEVICE_STATE_ACTIVE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFACE_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ **** IID_IMMDeviceEnumerator ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  _IMMDeviceCollection_GetCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _IMMDeviceCollection_Item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _IMMDeviceEnumerator_EnumAudioEndpoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _IMMDeviceEnumerator_GetDefaultAudioEndpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  eConsole ; 
 int /*<<< orphan*/  eRender ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ mmdevice_list_new (int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static IMMDevice *wasapi_init_device(const char *id)
{
   HRESULT hr;
   UINT32 dev_count, i;
   IMMDeviceEnumerator *enumerator = NULL;
   IMMDevice *device               = NULL;
   IMMDeviceCollection *collection = NULL;

   if (id)
   {
      RARCH_LOG("[WASAPI]: Initializing device %s ...\n", id);
   }
   else
   {
      RARCH_LOG("[WASAPI]: Initializing default device.. \n");
   }

#ifdef __cplusplus
   hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL,
         IID_IMMDeviceEnumerator, (void **)&enumerator);
#else
   hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL,
         &IID_IMMDeviceEnumerator, (void **)&enumerator);
#endif
   if (FAILED(hr))
      goto error;

   if (id)
   {
      int32_t idx_found        = -1;
      struct string_list *list = (struct string_list*)mmdevice_list_new(NULL);

      /* Search for device name first */
      if (list)
      {
         if (list->elems)
         {
            unsigned i;
            for (i = 0; i < list->size; i++)
            {
               RARCH_LOG("[WASAPI]: %d : %s\n", i, list->elems[i].data);
               if (string_is_equal(id, list->elems[i].data))
               {
                  idx_found = i;
                  break;
               }
            }
            /* Index was not found yet based on name string,
             * just assume id is a one-character number index. */

            if (idx_found == -1 && isdigit(id[0]))
            {
               idx_found = strtoul(id, NULL, 0);
               RARCH_LOG("[WASAPI]: Fallback, device index is a single number index instead: %d.\n", idx_found);

            }
         }
         string_list_free(list);
      }

      if (idx_found == -1)
         idx_found = 0;

      hr = _IMMDeviceEnumerator_EnumAudioEndpoints(enumerator,
            eRender, DEVICE_STATE_ACTIVE, &collection);
      if (FAILED(hr))
         goto error;

      hr = _IMMDeviceCollection_GetCount(collection, &dev_count);
      if (FAILED(hr))
         goto error;

      for (i = 0; i < dev_count; ++i)
      {
         hr = _IMMDeviceCollection_Item(collection, i, &device);
         if (FAILED(hr))
            goto error;

         if (i == idx_found)
            break;

         IFACE_RELEASE(device);
      }
   }
   else
   {
      hr = _IMMDeviceEnumerator_GetDefaultAudioEndpoint(
            enumerator, eRender, eConsole, &device);
      if (FAILED(hr))
         goto error;
   }

   if (!device)
      goto error;

   IFACE_RELEASE(collection);
   IFACE_RELEASE(enumerator);

   return device;

error:
   IFACE_RELEASE(collection);
   IFACE_RELEASE(enumerator);

   if (id)
   {
      RARCH_WARN("[WASAPI]: Failed to initialize device.\n");
   }
   else
   {
      RARCH_ERR("[WASAPI]: Failed to initialize device.\n");
   }

   return NULL;
}