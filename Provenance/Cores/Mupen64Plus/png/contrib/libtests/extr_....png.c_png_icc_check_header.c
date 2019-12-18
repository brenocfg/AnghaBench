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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_structrp ;
typedef  int /*<<< orphan*/  png_const_charp ;
typedef  scalar_t__* png_const_bytep ;
typedef  int /*<<< orphan*/ * png_colorspacerp ;

/* Variables and functions */
 int /*<<< orphan*/  D50_nCIEXYZ ; 
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_sRGB_INTENT_LAST ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int png_get_uint_32 (scalar_t__*) ; 
 int png_icc_profile_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 

int /* PRIVATE */
png_icc_check_header(png_const_structrp png_ptr, png_colorspacerp colorspace,
    png_const_charp name, png_uint_32 profile_length,
    png_const_bytep profile/* first 132 bytes only */, int color_type)
{
   png_uint_32 temp;

   /* Length check; this cannot be ignored in this code because profile_length
    * is used later to check the tag table, so even if the profile seems over
    * long profile_length from the caller must be correct.  The caller can fix
    * this up on read or write by just passing in the profile header length.
    */
   temp = png_get_uint_32(profile);
   if (temp != profile_length)
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "length does not match profile");

   temp = (png_uint_32) (*(profile+8));
   if (temp > 3 && (profile_length & 3))
      return png_icc_profile_error(png_ptr, colorspace, name, profile_length,
          "invalid length");

   temp = png_get_uint_32(profile+128); /* tag count: 12 bytes/tag */
   if (temp > 357913930 || /* (2^32-4-132)/12: maximum possible tag count */
      profile_length < 132+12*temp) /* truncated tag table */
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "tag count too large");

   /* The 'intent' must be valid or we can't store it, ICC limits the intent to
    * 16 bits.
    */
   temp = png_get_uint_32(profile+64);
   if (temp >= 0xffff) /* The ICC limit */
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "invalid rendering intent");

   /* This is just a warning because the profile may be valid in future
    * versions.
    */
   if (temp >= PNG_sRGB_INTENT_LAST)
      (void)png_icc_profile_error(png_ptr, NULL, name, temp,
          "intent outside defined range");

   /* At this point the tag table can't be checked because it hasn't necessarily
    * been loaded; however, various header fields can be checked.  These checks
    * are for values permitted by the PNG spec in an ICC profile; the PNG spec
    * restricts the profiles that can be passed in an iCCP chunk (they must be
    * appropriate to processing PNG data!)
    */

   /* Data checks (could be skipped).  These checks must be independent of the
    * version number; however, the version number doesn't accomodate changes in
    * the header fields (just the known tags and the interpretation of the
    * data.)
    */
   temp = png_get_uint_32(profile+36); /* signature 'ascp' */
   if (temp != 0x61637370)
      return png_icc_profile_error(png_ptr, colorspace, name, temp,
          "invalid signature");

   /* Currently the PCS illuminant/adopted white point (the computational
    * white point) are required to be D50,
    * however the profile contains a record of the illuminant so perhaps ICC
    * expects to be able to change this in the future (despite the rationale in
    * the introduction for using a fixed PCS adopted white.)  Consequently the
    * following is just a warning.
    */
   if (memcmp(profile+68, D50_nCIEXYZ, 12) != 0)
      (void)png_icc_profile_error(png_ptr, NULL, name, 0/*no tag value*/,
          "PCS illuminant is not D50");

   /* The PNG spec requires this:
    * "If the iCCP chunk is present, the image samples conform to the colour
    * space represented by the embedded ICC profile as defined by the
    * International Color Consortium [ICC]. The colour space of the ICC profile
    * shall be an RGB colour space for colour images (PNG colour types 2, 3, and
    * 6), or a greyscale colour space for greyscale images (PNG colour types 0
    * and 4)."
    *
    * This checking code ensures the embedded profile (on either read or write)
    * conforms to the specification requirements.  Notice that an ICC 'gray'
    * color-space profile contains the information to transform the monochrome
    * data to XYZ or L*a*b (according to which PCS the profile uses) and this
    * should be used in preference to the standard libpng K channel replication
    * into R, G and B channels.
    *
    * Previously it was suggested that an RGB profile on grayscale data could be
    * handled.  However it it is clear that using an RGB profile in this context
    * must be an error - there is no specification of what it means.  Thus it is
    * almost certainly more correct to ignore the profile.
    */
   temp = png_get_uint_32(profile+16); /* data colour space field */
   switch (temp)
   {
      case 0x52474220: /* 'RGB ' */
         if ((color_type & PNG_COLOR_MASK_COLOR) == 0)
            return png_icc_profile_error(png_ptr, colorspace, name, temp,
                "RGB color space not permitted on grayscale PNG");
         break;

      case 0x47524159: /* 'GRAY' */
         if ((color_type & PNG_COLOR_MASK_COLOR) != 0)
            return png_icc_profile_error(png_ptr, colorspace, name, temp,
                "Gray color space not permitted on RGB PNG");
         break;

      default:
         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "invalid ICC profile color space");
   }

   /* It is up to the application to check that the profile class matches the
    * application requirements; the spec provides no guidance, but it's pretty
    * weird if the profile is not scanner ('scnr'), monitor ('mntr'), printer
    * ('prtr') or 'spac' (for generic color spaces).  Issue a warning in these
    * cases.  Issue an error for device link or abstract profiles - these don't
    * contain the records necessary to transform the color-space to anything
    * other than the target device (and not even that for an abstract profile).
    * Profiles of these classes may not be embedded in images.
    */
   temp = png_get_uint_32(profile+12); /* profile/device class */
   switch (temp)
   {
      case 0x73636e72: /* 'scnr' */
      case 0x6d6e7472: /* 'mntr' */
      case 0x70727472: /* 'prtr' */
      case 0x73706163: /* 'spac' */
         /* All supported */
         break;

      case 0x61627374: /* 'abst' */
         /* May not be embedded in an image */
         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "invalid embedded Abstract ICC profile");

      case 0x6c696e6b: /* 'link' */
         /* DeviceLink profiles cannot be interpreted in a non-device specific
          * fashion, if an app uses the AToB0Tag in the profile the results are
          * undefined unless the result is sent to the intended device,
          * therefore a DeviceLink profile should not be found embedded in a
          * PNG.
          */
         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "unexpected DeviceLink ICC profile class");

      case 0x6e6d636c: /* 'nmcl' */
         /* A NamedColor profile is also device specific, however it doesn't
          * contain an AToB0 tag that is open to misinterpretation.  Almost
          * certainly it will fail the tests below.
          */
         (void)png_icc_profile_error(png_ptr, NULL, name, temp,
             "unexpected NamedColor ICC profile class");
         break;

      default:
         /* To allow for future enhancements to the profile accept unrecognized
          * profile classes with a warning, these then hit the test below on the
          * tag content to ensure they are backward compatible with one of the
          * understood profiles.
          */
         (void)png_icc_profile_error(png_ptr, NULL, name, temp,
             "unrecognized ICC profile class");
         break;
   }

   /* For any profile other than a device link one the PCS must be encoded
    * either in XYZ or Lab.
    */
   temp = png_get_uint_32(profile+20);
   switch (temp)
   {
      case 0x58595a20: /* 'XYZ ' */
      case 0x4c616220: /* 'Lab ' */
         break;

      default:
         return png_icc_profile_error(png_ptr, colorspace, name, temp,
             "unexpected ICC PCS encoding");
   }

   return 1;
}