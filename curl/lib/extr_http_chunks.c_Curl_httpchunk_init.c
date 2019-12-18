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
struct Curl_chunker {int /*<<< orphan*/  state; scalar_t__ dataleft; scalar_t__ hexindex; } ;
struct connectdata {struct Curl_chunker chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_HEX ; 

void Curl_httpchunk_init(struct connectdata *conn)
{
  struct Curl_chunker *chunk = &conn->chunk;
  chunk->hexindex = 0;      /* start at 0 */
  chunk->dataleft = 0;      /* no data left yet! */
  chunk->state = CHUNK_HEX; /* we get hex first! */
}