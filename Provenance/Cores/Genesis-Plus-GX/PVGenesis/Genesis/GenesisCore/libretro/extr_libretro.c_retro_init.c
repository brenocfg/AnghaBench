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
typedef  int /*<<< orphan*/  sms_ntsc_t ;
typedef  int /*<<< orphan*/  md_ntsc_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_ENVIRONMENT_SET_PERFORMANCE_LEVEL ; 
 int /*<<< orphan*/  RETRO_ENVIRONMENT_SET_PIXEL_FORMAT ; 
 unsigned int RETRO_PIXEL_FORMAT_RGB565 ; 
 void* calloc (int,int) ; 
 scalar_t__ environ_cb (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* md_ntsc ; 
 int /*<<< orphan*/  md_ntsc_composite ; 
 int /*<<< orphan*/  md_ntsc_init (void*,int /*<<< orphan*/ *) ; 
 void* sms_ntsc ; 
 int /*<<< orphan*/  sms_ntsc_composite ; 
 int /*<<< orphan*/  sms_ntsc_init (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void retro_init(void)
{
	unsigned level, rgb565;
#if defined(USE_NTSC)
   sms_ntsc = calloc(1, sizeof(sms_ntsc_t));
   md_ntsc  = calloc(1, sizeof(md_ntsc_t));
   sms_ntsc_init(sms_ntsc, &sms_ntsc_composite);
   md_ntsc_init(md_ntsc,   &md_ntsc_composite);
#endif

   level = 1;
   environ_cb(RETRO_ENVIRONMENT_SET_PERFORMANCE_LEVEL, &level);

#ifdef FRONTEND_SUPPORTS_RGB565
   rgb565 = RETRO_PIXEL_FORMAT_RGB565;
   if(environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &rgb565))
      fprintf(stderr, "Frontend supports RGB565 - will use that instead of XRGB1555.\n");
#endif
}