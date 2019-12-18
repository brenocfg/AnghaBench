#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_COMPARATOR_T ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ PARAMETER_T ;

/* Variables and functions */
 scalar_t__ parameter_comparator ; 
 int /*<<< orphan*/ * vc_containers_list_create (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_containers_list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_containers_list_insert (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vc_containers_list_validate (int /*<<< orphan*/ *) ; 
 scalar_t__ vc_uri_num_queries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_query (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINERS_LIST_T *fill_parameter_list(VC_URI_PARTS_T *uri)
{
   uint32_t num_parameters = vc_uri_num_queries(uri);
   VC_CONTAINERS_LIST_T *parameters;
   uint32_t ii;

   parameters = vc_containers_list_create(num_parameters, sizeof(PARAMETER_T), (VC_CONTAINERS_LIST_COMPARATOR_T)parameter_comparator);
   if (!parameters)
      return NULL;

   for (ii = 0; ii < num_parameters; ii++)
   {
      PARAMETER_T param;

      vc_uri_query(uri, ii, &param.name, &param.value);
      if (!vc_containers_list_insert(parameters, &param, false))
      {
         vc_containers_list_destroy(parameters);
         return NULL;
      }
   }

#ifdef RTP_DEBUG
   vc_containers_list_validate(parameters);
#endif

   return parameters;
}