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
typedef  int MMAL_STATUS_T ;

/* Variables and functions */
#define  MMAL_EAGAIN 142 
#define  MMAL_ECONFIG 141 
#define  MMAL_ECORRUPT 140 
#define  MMAL_EFAULT 139 
#define  MMAL_EINVAL 138 
#define  MMAL_EIO 137 
#define  MMAL_EISCONN 136 
#define  MMAL_ENOENT 135 
#define  MMAL_ENOMEM 134 
#define  MMAL_ENOSPC 133 
#define  MMAL_ENOSYS 132 
#define  MMAL_ENOTCONN 131 
#define  MMAL_ENOTREADY 130 
#define  MMAL_ENXIO 129 
#define  MMAL_ESPIPE 128 
 int MMAL_SUCCESS ; 
 int /*<<< orphan*/  vcos_log_error (char*) ; 

int mmal_status_to_int(MMAL_STATUS_T status)
{
   if (status == MMAL_SUCCESS)
      return 0;
   else
   {
      switch (status)
      {
      case MMAL_ENOMEM :
         vcos_log_error("Out of memory");
         break;
      case MMAL_ENOSPC :
         vcos_log_error("Out of resources (other than memory)");
         break;
      case MMAL_EINVAL:
         vcos_log_error("Argument is invalid");
         break;
      case MMAL_ENOSYS :
         vcos_log_error("Function not implemented");
         break;
      case MMAL_ENOENT :
         vcos_log_error("No such file or directory");
         break;
      case MMAL_ENXIO :
         vcos_log_error("No such device or address");
         break;
      case MMAL_EIO :
         vcos_log_error("I/O error");
         break;
      case MMAL_ESPIPE :
         vcos_log_error("Illegal seek");
         break;
      case MMAL_ECORRUPT :
         vcos_log_error("Data is corrupt \attention FIXME: not POSIX");
         break;
      case MMAL_ENOTREADY :
         vcos_log_error("Component is not ready \attention FIXME: not POSIX");
         break;
      case MMAL_ECONFIG :
         vcos_log_error("Component is not configured \attention FIXME: not POSIX");
         break;
      case MMAL_EISCONN :
         vcos_log_error("Port is already connected ");
         break;
      case MMAL_ENOTCONN :
         vcos_log_error("Port is disconnected");
         break;
      case MMAL_EAGAIN :
         vcos_log_error("Resource temporarily unavailable. Try again later");
         break;
      case MMAL_EFAULT :
         vcos_log_error("Bad address");
         break;
      default :
         vcos_log_error("Unknown status error");
         break;
      }

      return 1;
   }
}