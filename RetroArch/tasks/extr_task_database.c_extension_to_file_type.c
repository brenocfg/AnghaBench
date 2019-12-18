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
typedef  enum msg_file_type { ____Placeholder_msg_file_type } msg_file_type ;

/* Variables and functions */
 int FILE_TYPE_CHD ; 
 int FILE_TYPE_COMPRESSED ; 
 int FILE_TYPE_CUE ; 
 int FILE_TYPE_GDI ; 
 int FILE_TYPE_ISO ; 
 int FILE_TYPE_LUTRO ; 
 int FILE_TYPE_NONE ; 
 int FILE_TYPE_WBFS ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static enum msg_file_type extension_to_file_type(const char *ext)
{
   if (
         string_is_equal(ext, "7z")  ||
         string_is_equal(ext, "7Z")  ||
         string_is_equal(ext, "zip") ||
         string_is_equal(ext, "ZIP") ||
         string_is_equal(ext, "apk") ||
         string_is_equal(ext, "APK")
      )
      return FILE_TYPE_COMPRESSED;
   if (
         string_is_equal(ext, "cue")  ||
         string_is_equal(ext, "CUE")
      )
      return FILE_TYPE_CUE;
   if (
         string_is_equal(ext, "gdi")  ||
         string_is_equal(ext, "GDI")
      )
      return FILE_TYPE_GDI;
   if (
         string_is_equal(ext, "iso")  ||
         string_is_equal(ext, "ISO")
      )
      return FILE_TYPE_ISO;
   if (
         string_is_equal(ext, "chd")  ||
         string_is_equal(ext, "CHD")
      )
      return FILE_TYPE_CHD;
   if (
         string_is_equal(ext, "wbfs")  ||
         string_is_equal(ext, "WBFS")
      )
      return FILE_TYPE_WBFS;
   if (
         string_is_equal(ext, "lutro")  ||
         string_is_equal(ext, "LUTRO")
      )
      return FILE_TYPE_LUTRO;
   return FILE_TYPE_NONE;
}