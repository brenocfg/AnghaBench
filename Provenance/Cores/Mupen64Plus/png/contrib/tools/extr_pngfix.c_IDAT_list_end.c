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
struct IDAT_list {struct IDAT_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct IDAT_list) ; 
 int /*<<< orphan*/  IDAT_list_size (struct IDAT_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear (struct IDAT_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct IDAT_list*) ; 

__attribute__((used)) static void
IDAT_list_end(struct IDAT_list *IDAT_list)
{
   struct IDAT_list *list = IDAT_list->next;

   CLEAR(*IDAT_list);

   while (list != NULL)
   {
      struct IDAT_list *next = list->next;

      clear(list, IDAT_list_size(list, 0));
      free(list);
      list = next;
   }
}