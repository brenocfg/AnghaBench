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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  fcc ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENCODING_I420 ; 
 int /*<<< orphan*/  MMAL_ENCODING_OPAQUE ; 
 int /*<<< orphan*/  MMAL_ENCODING_UNKNOWN ; 
 int /*<<< orphan*/  MMAL_ENCODING_YUVUV128 ; 
 int /*<<< orphan*/  MMAL_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  MMAL_MIN (size_t,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int get_format(const char *name, uint32_t *fourcc, unsigned int *width, unsigned int *height)
{
   char *delim, fcc[4] = {' ', ' ', ' ', ' '};
   unsigned int value_u1, value_u2;
   size_t size;

   *width = *height = 0;
   *fourcc = MMAL_ENCODING_UNKNOWN;

   /* Fourcc is the first element */
   delim = strchr(name, ':');
   size = delim ? (size_t)(delim - name) : strlen(name);
   memcpy(fcc, name, MMAL_MIN(size, sizeof(fcc)));

   if (size == sizeof("yuv420")-1 && !memcmp(name, "yuv420", size))
      *fourcc = MMAL_ENCODING_I420;
   else if (size == sizeof("yuvuv")-1 && !memcmp(name, "yuvuv", size))
      *fourcc = MMAL_ENCODING_YUVUV128;
   else if (size == sizeof("opaque")-1 && !memcmp(name, "opaque", size))
      *fourcc = MMAL_ENCODING_OPAQUE;
   else if (size > 0 && size <= 4)
      *fourcc = MMAL_FOURCC(fcc[0], fcc[1], fcc[2], fcc[3]);
   else
      return 1;

   if (!delim)
      return 0; /* Nothing more to parse */

   /* Width/height are next */
   /* coverity[secure_coding] Only reading integers, so can't overflow */
   if (sscanf(delim+1, "%ux%u", &value_u1, &value_u2) != 2)
      return 1;

   *width = value_u1;
   *height = value_u2;
   return 0;
}