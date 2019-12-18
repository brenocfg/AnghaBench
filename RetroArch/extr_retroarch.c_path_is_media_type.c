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
typedef  int /*<<< orphan*/  ext_lower ;
typedef  enum rarch_content_type { ____Placeholder_rarch_content_type } rarch_content_type ;

/* Variables and functions */
#define  FILE_TYPE_3G2 164 
#define  FILE_TYPE_3GP 163 
#define  FILE_TYPE_ASF 162 
#define  FILE_TYPE_AVI 161 
#define  FILE_TYPE_BMP 160 
#define  FILE_TYPE_DIVX 159 
#define  FILE_TYPE_F4F 158 
#define  FILE_TYPE_F4V 157 
#define  FILE_TYPE_FLAC 156 
#define  FILE_TYPE_FLV 155 
#define  FILE_TYPE_GONG 154 
#define  FILE_TYPE_JPEG 153 
#define  FILE_TYPE_M2P 152 
#define  FILE_TYPE_M2TS 151 
#define  FILE_TYPE_M4A 150 
#define  FILE_TYPE_MKV 149 
#define  FILE_TYPE_MOD 148 
#define  FILE_TYPE_MOV 147 
#define  FILE_TYPE_MP3 146 
#define  FILE_TYPE_MP4 145 
#define  FILE_TYPE_MPEG 144 
#define  FILE_TYPE_MPG 143 
#define  FILE_TYPE_MXF 142 
#define  FILE_TYPE_NONE 141 
#define  FILE_TYPE_OGG 140 
#define  FILE_TYPE_OGM 139 
#define  FILE_TYPE_PNG 138 
#define  FILE_TYPE_PS 137 
#define  FILE_TYPE_S3M 136 
#define  FILE_TYPE_TGA 135 
#define  FILE_TYPE_TS 134 
#define  FILE_TYPE_VOB 133 
#define  FILE_TYPE_WAV 132 
#define  FILE_TYPE_WEBM 131 
#define  FILE_TYPE_WMA 130 
#define  FILE_TYPE_WMV 129 
#define  FILE_TYPE_XM 128 
 int RARCH_CONTENT_GONG ; 
 int RARCH_CONTENT_IMAGE ; 
 int RARCH_CONTENT_MOVIE ; 
 int RARCH_CONTENT_MUSIC ; 
 int RARCH_CONTENT_NONE ; 
 int /*<<< orphan*/  msg_hash_calculate (char*) ; 
 int msg_hash_to_file_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 int /*<<< orphan*/  string_to_lower (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strstr (char const*,char*) ; 

enum rarch_content_type path_is_media_type(const char *path)
{
   char ext_lower[128];

   ext_lower[0] = '\0';

   strlcpy(ext_lower, path_get_extension(path), sizeof(ext_lower));

   string_to_lower(ext_lower);

   /* hack, to detect livestreams so the ffmpeg core can be started */
   if (
      strstr(path, "udp://")  ||
      strstr(path, "http://") ||
      strstr(path, "https://")||
      strstr(path, "tcp://")  ||
      strstr(path, "rtmp://") ||
      strstr(path, "rtp://")
   )
      return RARCH_CONTENT_MOVIE;

   switch (msg_hash_to_file_type(msg_hash_calculate(ext_lower)))
   {
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
      case FILE_TYPE_OGM:
      case FILE_TYPE_MKV:
      case FILE_TYPE_AVI:
      case FILE_TYPE_MP4:
      case FILE_TYPE_FLV:
      case FILE_TYPE_WEBM:
      case FILE_TYPE_3GP:
      case FILE_TYPE_3G2:
      case FILE_TYPE_F4F:
      case FILE_TYPE_F4V:
      case FILE_TYPE_MOV:
      case FILE_TYPE_WMV:
      case FILE_TYPE_MPG:
      case FILE_TYPE_MPEG:
      case FILE_TYPE_VOB:
      case FILE_TYPE_ASF:
      case FILE_TYPE_DIVX:
      case FILE_TYPE_M2P:
      case FILE_TYPE_M2TS:
      case FILE_TYPE_PS:
      case FILE_TYPE_TS:
      case FILE_TYPE_MXF:
         return RARCH_CONTENT_MOVIE;
      case FILE_TYPE_WMA:
      case FILE_TYPE_OGG:
      case FILE_TYPE_MP3:
      case FILE_TYPE_M4A:
      case FILE_TYPE_FLAC:
      case FILE_TYPE_WAV:
         return RARCH_CONTENT_MUSIC;
#endif
#ifdef HAVE_IMAGEVIEWER
      case FILE_TYPE_JPEG:
      case FILE_TYPE_PNG:
      case FILE_TYPE_TGA:
      case FILE_TYPE_BMP:
         return RARCH_CONTENT_IMAGE;
#endif
#ifdef HAVE_IBXM
      case FILE_TYPE_MOD:
      case FILE_TYPE_S3M:
      case FILE_TYPE_XM:
         return RARCH_CONTENT_MUSIC;
#endif
#ifdef HAVE_EASTEREGG
      case FILE_TYPE_GONG:
         return RARCH_CONTENT_GONG;
#endif

      case FILE_TYPE_NONE:
      default:
         break;
   }

   return RARCH_CONTENT_NONE;
}