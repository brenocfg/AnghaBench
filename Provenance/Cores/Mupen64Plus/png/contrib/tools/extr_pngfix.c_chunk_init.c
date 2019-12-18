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
struct file {struct chunk* chunk; int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  data_pos; int /*<<< orphan*/  global; } ;
struct chunk {scalar_t__ compressed_digits; scalar_t__ uncompressed_digits; int /*<<< orphan*/  chunk_type; int /*<<< orphan*/  chunk_length; int /*<<< orphan*/  chunk_data_pos; int /*<<< orphan*/  global; struct file* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct chunk) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_init(struct chunk * const chunk, struct file * const file)
   /* When a chunk is initialized the file length/type/pos are copied into the
    * corresponding chunk fields and the new chunk is registered in the file
    * structure.  There can only be one chunk at a time.
    *
    * NOTE: this routine must onely be called from the file alloc routine!
    */
{
   assert(file->chunk == NULL);

   CLEAR(*chunk);

   chunk->file = file;
   chunk->global = file->global;

   chunk->chunk_data_pos = file->data_pos;
   chunk->chunk_length = file->length;
   chunk->chunk_type = file->type;

   /* Compresssed/uncompressed size information (from the zlib control structure
    * that is used to check the compressed data in a chunk.)
    */
   chunk->uncompressed_digits = 0;
   chunk->compressed_digits = 0;

   file->chunk = chunk;
}