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
typedef  void ct_font_renderer_t ;
typedef  int /*<<< orphan*/ * CTFontRef ;
typedef  int /*<<< orphan*/ * CGFontRef ;
typedef  int /*<<< orphan*/ * CGDataProviderRef ;
typedef  int /*<<< orphan*/ * CFURLRef ;
typedef  int /*<<< orphan*/ * CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFStringCreateWithCString (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CFURLCreateWithFileSystemPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CGDataProviderCreateWithURL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CGFontCreateWithDataProvider (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CTFontCreateWithGraphicsFont (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  coretext_font_renderer_create_atlas (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  font_renderer_ct_free (void*) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingASCII ; 
 int /*<<< orphan*/  kCFURLPOSIXPathStyle ; 
 int /*<<< orphan*/  path_is_valid (char const*) ; 

__attribute__((used)) static void *font_renderer_ct_init(const char *font_path, float font_size)
{
   char err                       = 0;
   CFStringRef cf_font_path       = NULL;
   CTFontRef face                 = NULL;
   CFURLRef url                   = NULL;
   CGDataProviderRef dataProvider = NULL;
   CGFontRef theCGFont            = NULL;
   ct_font_renderer_t *handle = (ct_font_renderer_t*)
      calloc(1, sizeof(*handle));

   if (!handle || !path_is_valid(font_path))
   {
      err = 1;
      goto error;
   }

   cf_font_path = CFStringCreateWithCString(
         NULL, font_path, kCFStringEncodingASCII);

   if (!cf_font_path)
   {
      err = 1;
      goto error;
   }

   url          = CFURLCreateWithFileSystemPath(
         kCFAllocatorDefault, cf_font_path, kCFURLPOSIXPathStyle, false);
   dataProvider = CGDataProviderCreateWithURL(url);
   theCGFont    = CGFontCreateWithDataProvider(dataProvider);
   face         = CTFontCreateWithGraphicsFont(theCGFont, font_size, NULL, NULL);

   if (!face)
   {
      err = 1;
      goto error;
   }

   if (!coretext_font_renderer_create_atlas(face, handle))
   {
      err = 1;
      goto error;
   }

error:
   if (err)
   {
      font_renderer_ct_free(handle);
      handle = NULL;
   }

   if (cf_font_path)
   {
      CFRelease(cf_font_path);
      cf_font_path = NULL;
   }
   if (face)
   {
      CFRelease(face);
      face = NULL;
   }
   if (url)
   {
      CFRelease(url);
      url = NULL;
   }
   if (dataProvider)
   {
      CFRelease(dataProvider);
      dataProvider = NULL;
   }
   if (theCGFont)
   {
      CFRelease(theCGFont);
      theCGFont = NULL;
   }

   return handle;
}