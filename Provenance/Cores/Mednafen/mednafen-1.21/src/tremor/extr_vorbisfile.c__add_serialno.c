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
typedef  int /*<<< orphan*/  ogg_uint32_t ;
typedef  int /*<<< orphan*/  ogg_page ;

/* Variables and functions */
 int /*<<< orphan*/ * _ogg_malloc (int) ; 
 int /*<<< orphan*/ * _ogg_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ogg_page_serialno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _add_serialno(ogg_page *og,ogg_uint32_t **serialno_list, int *n){
  ogg_uint32_t s = ogg_page_serialno(og);
  (*n)++;

  if(*serialno_list){
    *serialno_list = _ogg_realloc(*serialno_list, sizeof(**serialno_list)*(*n));
  }else{
    *serialno_list = _ogg_malloc(sizeof(**serialno_list));
  }

  (*serialno_list)[(*n)-1] = s;
}