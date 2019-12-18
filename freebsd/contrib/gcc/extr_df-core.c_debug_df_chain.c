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
struct df_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  df_chain_dump (struct df_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
debug_df_chain (struct df_link *link)
{
  df_chain_dump (link, stderr);
  fputc ('\n', stderr);
}