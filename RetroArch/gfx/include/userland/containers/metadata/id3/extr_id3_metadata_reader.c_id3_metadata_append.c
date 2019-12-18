#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int meta_num; TYPE_2__** meta; } ;
typedef  TYPE_1__ VC_CONTAINER_T ;
struct TYPE_11__ {scalar_t__ key; char* value; unsigned int size; } ;
typedef  TYPE_2__ VC_CONTAINER_METADATA_T ;
typedef  scalar_t__ VC_CONTAINER_METADATA_KEY_T ;

/* Variables and functions */
 unsigned int MIN (unsigned int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__** realloc (TYPE_2__**,int) ; 

__attribute__((used)) static VC_CONTAINER_METADATA_T *id3_metadata_append( VC_CONTAINER_T *p_ctx,
                                                     VC_CONTAINER_METADATA_KEY_T key,
                                                     unsigned int size )
{
   VC_CONTAINER_METADATA_T *meta, **p_meta;
   unsigned int i;

   for (i = 0; i != p_ctx->meta_num; ++i)
   {
      if (key == p_ctx->meta[i]->key) break;
   }

   /* Avoid duplicate entries for now */
   if (i < p_ctx->meta_num) return NULL;

   /* Sanity check size, truncate if necessary */
   size = MIN(size, 512);

   /* Allocate a new metadata entry */
   if((meta = malloc(sizeof(VC_CONTAINER_METADATA_T) + size)) == NULL)
      return NULL;

   /* We need to grow the array holding the metadata entries somehow, ideally,
      we'd like to use a linked structure of some sort but realloc is probably
      okay in this case */
   if((p_meta = realloc(p_ctx->meta, sizeof(VC_CONTAINER_METADATA_T *) * (p_ctx->meta_num + 1))) == NULL)
   {
      free(meta);
      return NULL;
   }

   p_ctx->meta = p_meta;
   memset(meta, 0, sizeof(VC_CONTAINER_METADATA_T) + size);
   p_ctx->meta[p_ctx->meta_num] = meta;
   meta->key = key;
   meta->value = (char *)&meta[1];
   meta->size = size;
   p_ctx->meta_num++;

   return meta;
}