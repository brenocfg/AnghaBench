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
typedef  int /*<<< orphan*/  libretrodb_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

libretrodb_t *libretrodb_new(void)
{
   libretrodb_t *db = (libretrodb_t*)calloc(1, sizeof(*db));

   if (!db)
      return NULL;

   return db;
}