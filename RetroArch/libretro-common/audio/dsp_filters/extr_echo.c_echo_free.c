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
struct echo_data {unsigned int num_channels; struct echo_data* channels; struct echo_data* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct echo_data*) ; 

__attribute__((used)) static void echo_free(void *data)
{
   unsigned i;
   struct echo_data *echo = (struct echo_data*)data;

   for (i = 0; i < echo->num_channels; i++)
      free(echo->channels[i].buffer);
   free(echo->channels);
   free(echo);
}