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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static ccv_array_t* uri_convnet_words_read(char* filename)
{
	FILE* r = fopen(filename, "rt");
	if(r)
	{
		ccv_array_t* words = ccv_array_new(sizeof(char*), 32, 0);
		size_t len = 1024;
		char* word = (char*)malloc(len);
		ssize_t read;
		while((read = getline(&word, &len, r)) != -1)
		{
			while(read > 1 && isspace(word[read - 1]))
				read--;
			word[read] = 0;
			char* new_word = (char*)malloc(sizeof(char) * (read + 1));
			memcpy(new_word, word, sizeof(char) * (read + 1));
			ccv_array_push(words, &new_word);
		}
		free(word);
		return words;
	}
	return 0;
}