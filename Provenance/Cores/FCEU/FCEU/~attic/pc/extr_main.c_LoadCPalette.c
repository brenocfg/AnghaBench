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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * FCEUD_UTF8fopen (char*,char*) ; 
 int /*<<< orphan*/  FCEUI_SetPaletteArray (int /*<<< orphan*/ *) ; 
 char* cpalette ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void LoadCPalette(void)
{
 uint8 tmpp[192];
 FILE *fp;

 if(!(fp=FCEUD_UTF8fopen(cpalette,"rb")))
 {
  printf(" Error loading custom palette from file: %s\n",cpalette);
  return;
 }
 fread(tmpp,1,192,fp);
 FCEUI_SetPaletteArray(tmpp);
 fclose(fp);
}