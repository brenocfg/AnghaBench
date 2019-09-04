#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  texture; scalar_t__ url; } ;
typedef  TYPE_1__ Texture ;

/* Variables and functions */
 int MAX_TEXTURES ; 
 int /*<<< orphan*/  create_texture () ; 
 int /*<<< orphan*/  load_texture_from_url (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 
 scalar_t__ strdup (char const*) ; 
 TYPE_1__* textures ; 

__attribute__((used)) static Texture *find_or_cache_url(const char *url)
{
  for(int i = 0; i < MAX_TEXTURES; ++i) // Naive O(n) lookup for tiny code size
    if (!strcmp(textures[i].url, url))
      return textures+i;
    else if (!textures[i].url)
    {
      textures[i].url = strdup(url);
      textures[i].texture = create_texture();
      load_texture_from_url(textures[i].texture, url, &textures[i].w, &textures[i].h);
      return textures+i;
    }
  return 0; // fail
}