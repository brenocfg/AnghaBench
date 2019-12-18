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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myexit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

s32 convert_bin_to_iso(FILE *bin_file, char *output_dir, char *iso_file_name,
 u32 sector_count)
{
  FILE *iso_file;
  u8 sector_buffer[2352];
  u32 i;

  chdir(output_dir);
  iso_file = fopen(iso_file_name, "wb");
  if (iso_file == NULL)
  {
    printf("failed to open: %s\n", iso_file_name);
    myexit(1);
  }
  printf("writing iso %s, %x sectors\n", iso_file_name, sector_count);

  for(i = 0; i < sector_count; i++)
  {
    printf("\b\b\b%3i", i*100 / sector_count);
    fflush(stdout);
    fread(sector_buffer, 2352, 1, bin_file);
    fwrite(sector_buffer + 16, 2048, 1, iso_file);
  }
  printf("\b\b\b100\n");

  fclose(iso_file);
  chdir("..");
  return 0;
}