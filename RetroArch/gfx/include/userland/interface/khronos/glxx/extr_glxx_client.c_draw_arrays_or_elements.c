#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  cache_info ;
struct TYPE_15__ {int send_any; TYPE_1__* entries; } ;
struct TYPE_12__ {scalar_t__ element_array; } ;
struct TYPE_14__ {TYPE_2__* attrib; int /*<<< orphan*/  cache; TYPE_3__ bound_buffer; int /*<<< orphan*/  (* render_callback ) () ;scalar_t__ default_framebuffer; } ;
struct TYPE_13__ {int send; char* start; char const* end; int next; } ;
struct TYPE_11__ {scalar_t__ buffer; char* pointer; int /*<<< orphan*/  stride; int /*<<< orphan*/  type; int /*<<< orphan*/  size; scalar_t__ enabled; } ;
struct TYPE_10__ {int cache_offset; int has_interlock; } ;
typedef  TYPE_4__ MERGE_INFO_T ;
typedef  char GLvoid ;
typedef  scalar_t__ GLuint ;
typedef  int GLsizei ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_5__ GLXX_CLIENT_STATE_T ;
typedef  TYPE_6__ GLXX_CACHE_INFO_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_ENTRY_T ; 
 scalar_t__ CACHE_SIG_ATTRIB_0 ; 
 int /*<<< orphan*/  GLINTDRAWELEMENTS_ID ; 
 int /*<<< orphan*/  GLINTFINDMAX_ID ; 
 int GLXX_CONFIG_MAX_VERTEX_ATTRIBS ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 int /*<<< orphan*/  GL_OUT_OF_MEMORY ; 
 scalar_t__ IS_OPENGLES_11 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_CALL3_RES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_CALL5_IN_CTRL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  RPC_ENUM (scalar_t__) ; 
 int RPC_INT_RES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_SIZEI (int) ; 
 int /*<<< orphan*/  RPC_UINT (scalar_t__) ; 
 int align_length (int) ; 
 int calc_length (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 int find_max (int,int,char const*) ; 
 int /*<<< orphan*/  glintDrawElements_impl ; 
 int /*<<< orphan*/  glintFindMax_impl ; 
 int /*<<< orphan*/  glxx_set_error (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int khrn_cache_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,scalar_t__) ; 
 int khrn_get_type_size (int) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static void draw_arrays_or_elements(CLIENT_THREAD_STATE_T *thread, GLXX_CLIENT_STATE_T *state, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
   uint32_t indices_offset = 0;
   GLuint indices_buffer;
   bool send_indices;
   int max = 0;
   int indices_length = 0;
   int indices_key = 0;
   int first = 0;
   int i, j, k;
   MERGE_INFO_T merge[GLXX_CONFIG_MAX_VERTEX_ATTRIBS];
   GLXX_CACHE_INFO_T cache_info;

   vcos_assert(state != NULL);

   if (state->render_callback && (IS_OPENGLES_11(thread) || state->default_framebuffer))
      state->render_callback();

   if(count<0)
   {
      glxx_set_error(state, GL_INVALID_VALUE);
      return;
   }

   cache_info.send_any = 0;
   for (i = 0; i < GLXX_CONFIG_MAX_VERTEX_ATTRIBS; i++)
   {
      if (state->attrib[i].enabled && state->attrib[i].buffer == 0)
      {
         cache_info.send_any = 1;

         /* TODO: what should we do if people give us null pointers? */
         if (state->attrib[i].pointer == NULL)
            return;
      }
   }

   if(type==0)
   {
      first = (int)indices;
      indices_offset = first;
      indices_buffer = 0;
      send_indices = 0;
      indices_key = 0;

      max = first + count - 1;
   }
   else
   {
      send_indices = count >= 0 && state->bound_buffer.element_array == 0;
      indices_buffer = state->bound_buffer.element_array;

      indices_length = align_length(count * khrn_get_type_size( (int) type ));
      if (send_indices)
      {
         max = find_max(count, khrn_get_type_size( (int)type ), indices);
         indices_key = khrn_cache_lookup(thread, &state->cache, indices, indices_length, 0);
         indices_offset = indices_key + offsetof(CACHE_ENTRY_T, data);
      }
      else
      {
         indices_key = 0;
         indices_offset = (uint32_t)indices;

         if (cache_info.send_any)
            max = RPC_INT_RES(RPC_CALL3_RES(
               glintFindMax_impl,
               thread,
               GLINTFINDMAX_ID,
               RPC_SIZEI(count),
               RPC_ENUM(type),
               RPC_UINT(indices_offset)));
         else
            max = -1;
      }
   }

   if (cache_info.send_any)
   {
      /* Merge overlapping arrays */
      for (i = 0; i < GLXX_CONFIG_MAX_VERTEX_ATTRIBS; i++)
      {
         if (state->attrib[i].enabled && state->attrib[i].buffer == 0)
         {
            merge[i].send = true;
            merge[i].start = state->attrib[i].pointer;
            merge[i].end = (const char *)state->attrib[i].pointer + calc_length(max, state->attrib[i].size, state->attrib[i].type, state->attrib[i].stride);
            merge[i].next = -1;

            for (j = 0; j < i; j++)
            {
               if (merge[j].send && merge[j].next == -1)
               {
                  const char *start = merge[i].start < merge[j].start ? merge[i].start : merge[j].start;
                  const char *end = merge[i].end > merge[j].end ? merge[i].end : merge[j].end;

                  if ((uint32_t)(end - start) < (uint32_t)((merge[i].end - merge[i].start) + (merge[j].end - merge[j].start)))
                  {
                     if (merge[i].start < merge[j].start)
                     {
                        k = i;
                        while (merge[k].next != -1)
                           k = merge[k].next;
                        merge[k].end = end;
                        merge[j].next = i;
                     }
                     else
                     {
                        vcos_assert(merge[j].next == -1);
                        merge[j].end = end;
                        merge[i].next = j;
                     }
                  }
               }
            }
         }
         else
         {
            merge[i].send = false;
         }
      }

      /* Perform cache lookups */
      for (i = 0; i < GLXX_CONFIG_MAX_VERTEX_ATTRIBS; i++)
      {
         if (merge[i].send && merge[i].next == -1)
         {
            int key = khrn_cache_lookup(thread, &state->cache, merge[i].start, merge[i].end - merge[i].start, CACHE_SIG_ATTRIB_0 + i);
            if (key == -1)
            {
               glxx_set_error(state, GL_OUT_OF_MEMORY);
               return;
            }
            cache_info.entries[i].cache_offset = key + offsetof(CACHE_ENTRY_T, data);
            cache_info.entries[i].has_interlock = 1;
         }
         else
         {
            cache_info.entries[i].cache_offset = ~0;
         }
      }

      /* Fill in the rest of cache_info (for the merged attribs which didn't force their own cache lookup) */
      for (i = 0; i < GLXX_CONFIG_MAX_VERTEX_ATTRIBS; i++)
      {
         if (merge[i].send && merge[i].next != -1)
         {
            k = i;
            while (merge[k].next != -1)
               k = merge[k].next;

            vcos_assert(k != -1);
            vcos_assert(cache_info.entries[k].cache_offset != ~0);
            cache_info.entries[i].cache_offset = cache_info.entries[k].cache_offset + ((size_t)state->attrib[i].pointer - (size_t)state->attrib[k].pointer);
            cache_info.entries[i].has_interlock = 0;
         }
      }

      /* Execute draw call, sending attrib cache information */
      RPC_CALL5_IN_CTRL(glintDrawElements_impl,
                thread,
                GLINTDRAWELEMENTS_ID,
                RPC_ENUM(mode),
                RPC_SIZEI(count),
                RPC_ENUM(type),
                RPC_UINT(indices_offset),
                &cache_info,
                sizeof(cache_info));
   }
   else
   {
      /* Execute draw call without sending any attrib cache information (except for send_any==0) */
      RPC_CALL5_IN_CTRL(glintDrawElements_impl,
                thread,
                GLINTDRAWELEMENTS_ID,
                RPC_ENUM(mode),
                RPC_SIZEI(count),
                RPC_ENUM(type),
                RPC_UINT(indices_offset),
                &cache_info,
                4/*sizeof(cache_info.send_any)*/);
   }
}