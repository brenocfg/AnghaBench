#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  config ;
typedef  int /*<<< orphan*/  VCOS_MUTEX_T ;
typedef  TYPE_1__* VCHIQ_INSTANCE_T ;
struct TYPE_9__ {int config_size; TYPE_3__* pconfig; } ;
typedef  TYPE_2__ VCHIQ_GET_CONFIG_T ;
struct TYPE_10__ {scalar_t__ version; TYPE_2__* version_min; } ;
typedef  TYPE_3__ VCHIQ_CONFIG_T ;
struct TYPE_8__ {int initialised; scalar_t__ fd; int use_close_delivered; int /*<<< orphan*/  mutex; scalar_t__ used_services; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  RETRY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_IOC_GET_CONFIG ; 
 int /*<<< orphan*/  VCHIQ_IOC_LIB_VERSION ; 
 TYPE_2__* VCHIQ_VERSION ; 
 scalar_t__ VCHIQ_VERSION_CLOSE_DELIVERED ; 
 scalar_t__ VCHIQ_VERSION_LIB_VERSION ; 
 scalar_t__ VCHIQ_VERSION_MIN ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ dup (int const) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_default_lib_log_level ; 
 TYPE_1__ vchiq_instance ; 
 int /*<<< orphan*/  vchiq_lib_log_category ; 
 int /*<<< orphan*/  vcos_global_lock () ; 
 int /*<<< orphan*/  vcos_global_unlock () ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCHIQ_INSTANCE_T
vchiq_lib_init(const int dev_vchiq_fd)
{
   static int mutex_initialised = 0;
   static VCOS_MUTEX_T vchiq_lib_mutex;
   VCHIQ_INSTANCE_T instance = &vchiq_instance;

   vcos_global_lock();
   if (!mutex_initialised)
   {
      vcos_mutex_create(&vchiq_lib_mutex, "vchiq-init");

      vcos_log_set_level( &vchiq_lib_log_category, vchiq_default_lib_log_level );
      vcos_log_register( "vchiq_lib", &vchiq_lib_log_category );

      mutex_initialised = 1;
   }
   vcos_global_unlock();

   vcos_mutex_lock(&vchiq_lib_mutex);

   if (instance->initialised == 0)
   {
      instance->fd = dev_vchiq_fd == -1 ?
         open("/dev/vchiq", O_RDWR) :
         dup(dev_vchiq_fd);
      if (instance->fd >= 0)
      {
         VCHIQ_GET_CONFIG_T args;
         VCHIQ_CONFIG_T config;
         int ret;
         args.config_size = sizeof(config);
         args.pconfig = &config;
         RETRY(ret, ioctl(instance->fd, VCHIQ_IOC_GET_CONFIG, &args));
         if ((ret == 0) && (config.version >= VCHIQ_VERSION_MIN) && (config.version_min <= VCHIQ_VERSION))
         {
            if (config.version >= VCHIQ_VERSION_LIB_VERSION)
            {
               RETRY(ret, ioctl(instance->fd, VCHIQ_IOC_LIB_VERSION, VCHIQ_VERSION));
            }
            if (ret == 0)
            {
               instance->used_services = 0;
               instance->use_close_delivered = (config.version >= VCHIQ_VERSION_CLOSE_DELIVERED);
               vcos_mutex_create(&instance->mutex, "VCHIQ instance");
               instance->initialised = 1;
            }
         }
         else
         {
            if (ret == 0)
            {
               vcos_log_error("Incompatible VCHIQ library - driver version %d (min %d), library version %d (min %d)",
                  config.version, config.version_min, VCHIQ_VERSION, VCHIQ_VERSION_MIN);
            }
            else
            {
               vcos_log_error("Very incompatible VCHIQ library - cannot retrieve driver version");
            }
            close(instance->fd);
            instance = NULL;
         }
      }
      else
      {
         instance = NULL;
      }
   }
   else if (instance->initialised > 0)
   {
      instance->initialised++;
   }

   vcos_mutex_unlock(&vchiq_lib_mutex);

   return instance;
}