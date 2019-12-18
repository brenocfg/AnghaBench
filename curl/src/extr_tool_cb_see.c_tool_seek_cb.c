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
struct InStruct {int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ curl_off_t ;

/* Variables and functions */
 int CURL_SEEKFUNC_CANTSEEK ; 
 int CURL_SEEKFUNC_FAIL ; 
 int CURL_SEEKFUNC_OK ; 
 scalar_t__ LSEEK_ERROR ; 
 long OUR_MAX_SEEK_L ; 
 scalar_t__ OUR_MAX_SEEK_O ; 
 int SEEK_CUR ; 
 int SEEK_SET ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int) ; 

int tool_seek_cb(void *userdata, curl_off_t offset, int whence)
{
  struct InStruct *in = userdata;

#if(CURL_SIZEOF_CURL_OFF_T > SIZEOF_OFF_T) && !defined(USE_WIN32_LARGE_FILES)

  /* The offset check following here is only interesting if curl_off_t is
     larger than off_t and we are not using the WIN32 large file support
     macros that provide the support to do 64bit seeks correctly */

  if(offset > OUR_MAX_SEEK_O) {
    /* Some precaution code to work around problems with different data sizes
       to allow seeking >32bit even if off_t is 32bit. Should be very rare and
       is really valid on weirdo-systems. */
    curl_off_t left = offset;

    if(whence != SEEK_SET)
      /* this code path doesn't support other types */
      return CURL_SEEKFUNC_FAIL;

    if(LSEEK_ERROR == lseek(in->fd, 0, SEEK_SET))
      /* couldn't rewind to beginning */
      return CURL_SEEKFUNC_FAIL;

    while(left) {
      long step = (left > OUR_MAX_SEEK_O) ? OUR_MAX_SEEK_L : (long)left;
      if(LSEEK_ERROR == lseek(in->fd, step, SEEK_CUR))
        /* couldn't seek forwards the desired amount */
        return CURL_SEEKFUNC_FAIL;
      left -= step;
    }
    return CURL_SEEKFUNC_OK;
  }
#endif

  if(LSEEK_ERROR == lseek(in->fd, offset, whence))
    /* couldn't rewind, the reason is in errno but errno is just not portable
       enough and we don't actually care that much why we failed. We'll let
       libcurl know that it may try other means if it wants to. */
    return CURL_SEEKFUNC_CANTSEEK;

  return CURL_SEEKFUNC_OK;
}