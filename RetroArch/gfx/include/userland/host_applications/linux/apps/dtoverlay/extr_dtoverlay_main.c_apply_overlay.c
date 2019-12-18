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
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_MODE ; 
 scalar_t__ dir_exists (char const*) ; 
 int /*<<< orphan*/  dt_overlays_dir ; 
 int /*<<< orphan*/  dtoverlay_free_dtb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtoverlay_load_dtb (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ dtoverlay_save_dtb (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  free_string (char const*) ; 
 scalar_t__ mkdir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  overlay_applied (char const*) ; 
 int /*<<< orphan*/  rmdir (char const*) ; 
 char* sprintf_dup (char*,char const*,...) ; 

__attribute__((used)) static int apply_overlay(const char *overlay_file, const char *overlay)
{
    const char *overlay_dir = sprintf_dup("%s/%s", dt_overlays_dir, overlay);
    int ret = 0;
    if (dir_exists(overlay_dir))
    {
	error("Overlay '%s' is already loaded", overlay);
    }
    else if (mkdir(overlay_dir, DIR_MODE) == 0)
    {
	DTBLOB_T *dtb = dtoverlay_load_dtb(overlay_file, 0);
	if (!dtb)
	{
	    error("Failed to apply overlay '%s' (load)", overlay);
	}
	else
	{
	    const char *dest_file = sprintf_dup("%s/dtbo", overlay_dir);

	    /* then write the overlay to the file */
	    if (dtoverlay_save_dtb(dtb, dest_file) != 0)
		error("Failed to apply overlay '%s' (save)", overlay);
	    else if (!overlay_applied(overlay_dir))
		error("Failed to apply overlay '%s' (kernel)", overlay);
	    else
		ret = 1;

	    free_string(dest_file);
	    dtoverlay_free_dtb(dtb);
	}

	if (!ret)
		rmdir(overlay_dir);
    }
    else
    {
	error("Failed to create overlay directory");
    }

    return ret;
}