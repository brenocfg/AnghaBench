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
typedef  enum file_path_enum { ____Placeholder_file_path_enum } file_path_enum ;

/* Variables and functions */
#define  FILE_PATH_7Z_EXTENSION 193 
#define  FILE_PATH_ASSETS_ZIP 192 
#define  FILE_PATH_AUTOCONFIG_ZIP 191 
#define  FILE_PATH_AUTO_EXTENSION 190 
#define  FILE_PATH_BACKGROUND_IMAGE 189 
#define  FILE_PATH_BMP_EXTENSION 188 
#define  FILE_PATH_BPS_EXTENSION 187 
#define  FILE_PATH_BSV_EXTENSION 186 
#define  FILE_PATH_CGP_EXTENSION 185 
#define  FILE_PATH_CHEATS_ZIP 184 
#define  FILE_PATH_CHT_EXTENSION 183 
#define  FILE_PATH_CONFIG_EXTENSION 182 
#define  FILE_PATH_CONTENT_BASENAME 181 
#define  FILE_PATH_CONTENT_FAVORITES 180 
#define  FILE_PATH_CONTENT_HISTORY 179 
#define  FILE_PATH_CONTENT_IMAGE_HISTORY 178 
#define  FILE_PATH_CONTENT_MUSIC_HISTORY 177 
#define  FILE_PATH_CONTENT_VIDEO_HISTORY 176 
#define  FILE_PATH_CORE_INFO_EXTENSION 175 
#define  FILE_PATH_CORE_INFO_ZIP 174 
#define  FILE_PATH_CORE_OPTIONS_CONFIG 173 
#define  FILE_PATH_CORE_THUMBNAILPACKS_URL 172 
#define  FILE_PATH_CORE_THUMBNAILS_URL 171 
#define  FILE_PATH_DATABASE_RDB_ZIP 170 
#define  FILE_PATH_DEFAULT_EVENT_LOG 169 
#define  FILE_PATH_DETECT 168 
#define  FILE_PATH_EVENT_LOG_EXTENSION 167 
#define  FILE_PATH_FLAC_EXTENSION 166 
#define  FILE_PATH_GLSLP_EXTENSION 165 
#define  FILE_PATH_INDEX_DIRS_URL 164 
#define  FILE_PATH_INDEX_EXTENDED_URL 163 
#define  FILE_PATH_INDEX_URL 162 
#define  FILE_PATH_IPS_EXTENSION 161 
#define  FILE_PATH_JPEG_EXTENSION 160 
#define  FILE_PATH_JPG_EXTENSION 159 
#define  FILE_PATH_LAKKA_URL 158 
#define  FILE_PATH_LPL_EXTENSION 157 
#define  FILE_PATH_LPL_EXTENSION_NO_DOT 156 
#define  FILE_PATH_LUTRO_PLAYLIST 155 
#define  FILE_PATH_MAIN_CONFIG 154 
#define  FILE_PATH_MOD_EXTENSION 153 
#define  FILE_PATH_MP3_EXTENSION 152 
#define  FILE_PATH_NETPLAY_ROOM_LIST_URL 151 
#define  FILE_PATH_NUL 150 
#define  FILE_PATH_OGG_EXTENSION 149 
#define  FILE_PATH_OPT_EXTENSION 148 
#define  FILE_PATH_OVERLAYS_ZIP 147 
#define  FILE_PATH_PNG_EXTENSION 146 
#define  FILE_PATH_RDB_EXTENSION 145 
#define  FILE_PATH_REMAP_EXTENSION 144 
#define  FILE_PATH_RTC_EXTENSION 143 
#define  FILE_PATH_RUNTIME_EXTENSION 142 
#define  FILE_PATH_S3M_EXTENSION 141 
#define  FILE_PATH_SHADERS_CG_ZIP 140 
#define  FILE_PATH_SHADERS_GLSL_ZIP 139 
#define  FILE_PATH_SHADERS_SLANG_ZIP 138 
#define  FILE_PATH_SLANGP_EXTENSION 137 
#define  FILE_PATH_SRM_EXTENSION 136 
#define  FILE_PATH_STATE_EXTENSION 135 
#define  FILE_PATH_TGA_EXTENSION 134 
#define  FILE_PATH_TTF_FONT 133 
#define  FILE_PATH_UNKNOWN 132 
#define  FILE_PATH_UPS_EXTENSION 131 
#define  FILE_PATH_WAV_EXTENSION 130 
#define  FILE_PATH_XM_EXTENSION 129 
#define  FILE_PATH_ZIP_EXTENSION 128 

const char *file_path_str(enum file_path_enum enum_idx)
{
   const char *str = "null";

   switch (enum_idx)
   {
      case FILE_PATH_DETECT:
         str = "DETECT";
         break;
      case FILE_PATH_CONTENT_BASENAME:
         str = "content.png";
         break;
      case FILE_PATH_LUTRO_PLAYLIST:
         str = "Lutro.lpl";
         break;
      case FILE_PATH_NUL:
         str = "nul";
         break;
      case FILE_PATH_CGP_EXTENSION:
         str = ".cgp";
         break;
      case FILE_PATH_GLSLP_EXTENSION:
         str = ".glslp";
         break;
      case FILE_PATH_SLANGP_EXTENSION:
         str = ".slangp";
         break;
      case FILE_PATH_AUTO_EXTENSION:
         str = ".auto";
         break;
      case FILE_PATH_BSV_EXTENSION:
         str = ".bsv";
         break;
      case FILE_PATH_OPT_EXTENSION:
         str = ".opt";
         break;
      case FILE_PATH_CORE_INFO_EXTENSION:
         str = ".info";
         break;
      case FILE_PATH_CONFIG_EXTENSION:
         str = ".cfg";
         break;
      case FILE_PATH_REMAP_EXTENSION:
         str = ".rmp";
         break;
      case FILE_PATH_RTC_EXTENSION:
         str = ".rtc";
         break;
      case FILE_PATH_CHT_EXTENSION:
         str = ".cht";
         break;
      case FILE_PATH_SRM_EXTENSION:
         str = ".srm";
         break;
      case FILE_PATH_STATE_EXTENSION:
         str = ".state";
         break;
      case FILE_PATH_LPL_EXTENSION:
         str = ".lpl";
         break;
      case FILE_PATH_LPL_EXTENSION_NO_DOT:
         str = "lpl";
         break;
      case FILE_PATH_PNG_EXTENSION:
         str = ".png";
         break;
      case FILE_PATH_MP3_EXTENSION:
         str = ".mp3";
         break;
      case FILE_PATH_FLAC_EXTENSION:
         str = ".flac";
         break;
      case FILE_PATH_OGG_EXTENSION:
         str = ".ogg";
         break;
      case FILE_PATH_WAV_EXTENSION:
         str = ".wav";
         break;
      case FILE_PATH_MOD_EXTENSION:
         str = ".mod";
         break;
      case FILE_PATH_S3M_EXTENSION:
         str = ".s3m";
         break;
      case FILE_PATH_XM_EXTENSION:
         str = ".xm";
         break;
      case FILE_PATH_JPEG_EXTENSION:
         str = ".jpeg";
         break;
      case FILE_PATH_BMP_EXTENSION:
         str = ".bmp";
         break;
      case FILE_PATH_TGA_EXTENSION:
         str = ".tga";
         break;
      case FILE_PATH_JPG_EXTENSION:
         str = ".jpg";
         break;
      case FILE_PATH_UPS_EXTENSION:
         str = ".ups";
         break;
      case FILE_PATH_IPS_EXTENSION:
         str = ".ips";
         break;
      case FILE_PATH_BPS_EXTENSION:
         str = ".bps";
         break;
      case FILE_PATH_RDB_EXTENSION:
         str = ".rdb";
         break;
      case FILE_PATH_ZIP_EXTENSION:
         str = ".zip";
         break;
      case FILE_PATH_7Z_EXTENSION:
         str = ".7z";
         break;
      case FILE_PATH_INDEX_URL:
         str = ".index";
         break;
      case FILE_PATH_INDEX_DIRS_URL:
         str = ".index-dirs";
         break;
      case FILE_PATH_INDEX_EXTENDED_URL:
         str = ".index-extended";
         break;
      case FILE_PATH_NETPLAY_ROOM_LIST_URL:
         str = "registry.lpl";
         break;
      case FILE_PATH_CORE_THUMBNAILS_URL:
         str = "http://thumbnails.libretro.com";
         break;
      case FILE_PATH_CORE_THUMBNAILPACKS_URL:
         str = "http://thumbnailpacks.libretro.com";
         break;
      case FILE_PATH_LAKKA_URL:
#ifdef HAVE_LAKKA_NIGHTLY
         str = "http://nightly.builds.lakka.tv/.updater";
#else
         str = "http://le.builds.lakka.tv";
#endif
         break;
      case FILE_PATH_SHADERS_GLSL_ZIP:
         str = "shaders_glsl.zip";
         break;
      case FILE_PATH_SHADERS_SLANG_ZIP:
         str = "shaders_slang.zip";
         break;
      case FILE_PATH_SHADERS_CG_ZIP:
         str = "shaders_cg.zip";
         break;
      case FILE_PATH_DATABASE_RDB_ZIP:
         str = "database-rdb.zip";
         break;
      case FILE_PATH_OVERLAYS_ZIP:
         str = "overlays.zip";
         break;
      case FILE_PATH_CORE_INFO_ZIP:
         str = "info.zip";
         break;
      case FILE_PATH_CHEATS_ZIP:
         str = "cheats.zip";
         break;
      case FILE_PATH_ASSETS_ZIP:
         str = "assets.zip";
         break;
      case FILE_PATH_AUTOCONFIG_ZIP:
         str = "autoconfig.zip";
         break;
      case FILE_PATH_CONTENT_HISTORY:
         str = "content_history.lpl";
         break;
      case FILE_PATH_CONTENT_FAVORITES:
         str = "content_favorites.lpl";
         break;
      case FILE_PATH_CONTENT_MUSIC_HISTORY:
         str = "content_music_history.lpl";
         break;
      case FILE_PATH_CONTENT_VIDEO_HISTORY:
         str = "content_video_history.lpl";
         break;
      case FILE_PATH_CONTENT_IMAGE_HISTORY:
         str = "content_image_history.lpl";
         break;
      case FILE_PATH_CORE_OPTIONS_CONFIG:
         str = "retroarch-core-options.cfg";
         break;
      case FILE_PATH_MAIN_CONFIG:
         str = "retroarch.cfg";
         break;
      case FILE_PATH_BACKGROUND_IMAGE:
         str = "bg.png";
         break;
      case FILE_PATH_TTF_FONT:
         str = "font.ttf";
         break;
      case FILE_PATH_RUNTIME_EXTENSION:
         str = ".lrtl";
         break;
      case FILE_PATH_DEFAULT_EVENT_LOG:
         str = "retroarch.log";
         break;
      case FILE_PATH_EVENT_LOG_EXTENSION:
         str = ".log";
         break;
      case FILE_PATH_UNKNOWN:
      default:
         break;
   }

   return str;
}