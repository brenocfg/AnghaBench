#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int tracks_num; TYPE_2__* priv; TYPE_5__** tracks; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {int init; int /*<<< orphan*/  default_block_size; int /*<<< orphan*/  block_size; TYPE_5__* track; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
typedef  scalar_t__ VC_CONTAINER_FOURCC_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_T ;
struct TYPE_19__ {scalar_t__ codec; scalar_t__ ext; int /*<<< orphan*/  type; } ;
struct TYPE_18__ {int is_enabled; TYPE_1__* format; } ;
struct TYPE_15__ {int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  pf_close; TYPE_4__* module; int /*<<< orphan*/  uri; } ;
struct TYPE_14__ {scalar_t__ codec; int /*<<< orphan*/  es_type; } ;
struct TYPE_13__ {scalar_t__ codec; int /*<<< orphan*/  type; scalar_t__ ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BLOCK_SIZE ; 
 int /*<<< orphan*/  DEFAULT_JPEG_BLOCK_SIZE ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VC_CONTAINER_CODEC_JPEG ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 TYPE_11__* bin_extension_to_format_table ; 
 int /*<<< orphan*/  binary_reader_close ; 
 int /*<<< orphan*/  binary_reader_read ; 
 int /*<<< orphan*/  binary_reader_seek ; 
 TYPE_9__* extension_to_format_table ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcasecmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  strstr (char const*,scalar_t__) ; 
 TYPE_5__* vc_container_allocate_track (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_find_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 char const* vc_uri_path (int /*<<< orphan*/ ) ; 
 char* vc_uri_path_extension (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T binary_reader_open( VC_CONTAINER_T *p_ctx )
{
   const char *extension = vc_uri_path_extension(p_ctx->priv->uri);
   VC_CONTAINER_MODULE_T *module = 0;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_INVALID;
   VC_CONTAINER_ES_TYPE_T es_type = 0;
   VC_CONTAINER_FOURCC_T codec = 0;
   unsigned int i;

   /* Check if the user has specified a container */
   vc_uri_find_query(p_ctx->priv->uri, 0, "container", &extension);

   /* Check if the extension is supported */
   if(!extension || !vc_uri_path(p_ctx->priv->uri))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   for(i = 0; extension_to_format_table[i].ext; i++)
   {
      if(strcasecmp(extension, extension_to_format_table[i].ext))
         continue;

      es_type = extension_to_format_table[i].type;
      codec = extension_to_format_table[i].codec;
      break;
   }
   if(!extension_to_format_table[i].ext) return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* If this a .bin file we look in our bin list */
   for(i = 0; !codec && bin_extension_to_format_table[i].ext; i++)
   {
      if(!strstr(vc_uri_path(p_ctx->priv->uri), bin_extension_to_format_table[i].ext) &&
         !strstr(extension, bin_extension_to_format_table[i].ext))
         continue;

      es_type = bin_extension_to_format_table[i].type;
      codec = bin_extension_to_format_table[i].codec;
      break;
   }
   if(!codec) return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Allocate our context */
   module = malloc(sizeof(*module));
   if(!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;
   p_ctx->tracks_num = 1;
   p_ctx->tracks = &module->track;
   p_ctx->tracks[0] = vc_container_allocate_track(p_ctx, 0);
   if(!p_ctx->tracks[0]) return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   p_ctx->tracks[0]->format->es_type = es_type;
   p_ctx->tracks[0]->format->codec = codec;
   p_ctx->tracks[0]->is_enabled = true;
   module->default_block_size = DEFAULT_BLOCK_SIZE;
   if(codec == VC_CONTAINER_CODEC_JPEG)
      module->default_block_size = DEFAULT_JPEG_BLOCK_SIZE;
   module->block_size = module->default_block_size;
   module->init = 1;

   /*
    *  We now have all the information we really need to start playing the stream
    */

   p_ctx->priv->pf_close = binary_reader_close;
   p_ctx->priv->pf_read = binary_reader_read;
   p_ctx->priv->pf_seek = binary_reader_seek;
   return VC_CONTAINER_SUCCESS;

 error:
   LOG_DEBUG(p_ctx, "binary: error opening stream (%i)", status);
   return status;
}