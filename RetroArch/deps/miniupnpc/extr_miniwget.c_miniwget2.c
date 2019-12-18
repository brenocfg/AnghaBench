__attribute__((used)) static void *
miniwget2(const char * host,
          unsigned short port, const char * path,
          int * size, char * addr_str, int addr_str_len,
          unsigned int scope_id, int * status_code)
{
	char * respbuffer;

#if 1
	respbuffer = (char*)miniwget3(host, port, path, size,
	                       addr_str, addr_str_len, "1.1",
	                       scope_id, status_code);
#else
	respbuffer = (char*)miniwget3(host, port, path, size,
	                       addr_str, addr_str_len, "1.0",
	                       scope_id, status_code);
	if (*size == 0)
	{
#ifdef DEBUG
		printf("Retrying with HTTP/1.1\n");
#endif
		free(respbuffer);
		respbuffer = miniwget3(host, port, path, size,
		                       addr_str, addr_str_len, "1.1",
		                       scope_id, status_code);
	}
#endif
	return respbuffer;
}