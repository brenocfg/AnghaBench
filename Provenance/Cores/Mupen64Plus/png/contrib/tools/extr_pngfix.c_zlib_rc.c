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
struct zlib {int rc; } ;

/* Variables and functions */
#define  Z_BUF_ERROR 136 
#define  Z_DATA_ERROR 135 
#define  Z_ERRNO 134 
#define  Z_MEM_ERROR 133 
#define  Z_NEED_DICT 132 
#define  Z_OK 131 
#define  Z_STREAM_END 130 
#define  Z_STREAM_ERROR 129 
#define  Z_VERSION_ERROR 128 

__attribute__((used)) static const char *
zlib_rc(struct zlib *zlib)
   /* Return a string for the zlib return code */
{
   switch (zlib->rc)
   {
      case Z_OK:              return "Z_OK";
      case Z_STREAM_END:      return "Z_STREAM_END";
      case Z_NEED_DICT:       return "Z_NEED_DICT";
      case Z_ERRNO:           return "Z_ERRNO";
      case Z_STREAM_ERROR:    return "Z_STREAM_ERROR";
      case Z_DATA_ERROR:      return "Z_DATA_ERROR";
      case Z_MEM_ERROR:       return "Z_MEM_ERROR";
      case Z_BUF_ERROR:       return "Z_BUF_ERROR";
      case Z_VERSION_ERROR:   return "Z_VERSION_ERROR";
      default:                return "Z_*INVALID_RC*";
   }
}