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
struct md5_ctx {int dummy; } ;

/* Variables and functions */
 void* md5_finish_ctx (struct md5_ctx*,void*) ; 
 int /*<<< orphan*/  md5_init_ctx (struct md5_ctx*) ; 
 int /*<<< orphan*/  md5_process_bytes (char const*,size_t,struct md5_ctx*) ; 

void *
md5_buffer (const char *buffer, size_t len, void *resblock)
{
  struct md5_ctx ctx;

  /* Initialize the computation context.  */
  md5_init_ctx (&ctx);

  /* Process whole buffer but last len % 64 bytes.  */
  md5_process_bytes (buffer, len, &ctx);

  /* Put result in desired memory area.  */
  return md5_finish_ctx (&ctx, resblock);
}