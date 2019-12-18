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
typedef  int /*<<< orphan*/  gx_texture ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  gxCopyScreenshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gxTextureWritePNG (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void gxSaveScreenshot(char *filename)
{
  /* capture screenshot into a texture */
  gx_texture texture;
  gxCopyScreenshot(&texture);

  /* open PNG file */
  FILE *f = fopen(filename,"wb");
  if (f)
  {
    /* encode screenshot into PNG file */
    gxTextureWritePNG(&texture,f);
    fclose(f);
  }
}